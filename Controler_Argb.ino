// ================== LIBS ==================
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>
#include "RotaryEncoder.h"
#include <FastLED.h>
#include <EEPROM.h>

//defined (TFT 2.8 ESP8266) ======
#define TFT_CS         4
#define TFT_RST        0
#define TFT_DC         2


//defined FastLed ================
#define DATA_PIN    15
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB
#define NUM_LEDS    17
#define FRAMES_PER_SECOND  120

//defined Encoder ================
byte STEPS = 1;
//  #define POSMIN 0
//  #define POSMAX 2
#define BtnEnc 3

// ================== OBJECTS ==================
RotaryEncoder encoder(16, 5);
// For 1.14", 1.3", 1.54", 1.69", and 2.0" TFT with ST7789:
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

// #if !defined(ESP8266)
//   Adafruit_ST7789(SPIClass *spiClass, TFT_CS, TFT_DC, TFT_RST);
// #endif // end !ESP8266

int lastPos = 0, newPos = 0;
int limitPointer = 255;
int pointer = 0;
int memor = 0;
boolean flag = true;
boolean btn;
boolean btnFlag = false;
boolean PassFlag = false;
boolean flagPassColorMode = true;
boolean flagPassTime = true;
uint8_t gHue = 0;
CRGB leds[NUM_LEDS];
byte SizeText = 3;

byte POSMIN = 0;
byte POSMAX = 0;

unsigned long last_time;
unsigned long time_work;

unsigned long ee_time;
boolean ee_request = false;
byte Size_EEPROM = 6;

int Sec;

struct {
  byte IdMenu = 0;
  byte IdColorMode = 0;
  byte IdColorEffects = 0;
  byte IdOneColor = 0;
  byte BRIGHTNESS = 70;
  byte speedColorEffect = 50;
  byte CountDisplayBRG = 100;
} settings;

uint8_t MasMenu[] = {20, 60, 100}; //20/60/100/140/180|  Масив відповідальний за положення вказівника, та за переміщення по меню
uint8_t MasColor[] = {20, 200};  //Масив відповідальний за положення вказівника, та за переміщення по під меню "Color"
char* StrNameMode[] = {"Off", "One color", "Effects"};
char* MemorNameMode = StrNameMode[settings.IdColorMode];

char* StrNameEffect[] = {"rainbow_fade|", "rainbow_loop|", "random_burst|", "color_bounce|", "DontWork|", "RB_bounce|", "rainbow|"};
//Масив відповідальний за назву ефектів, для подальшого виведення іх на дисплей
char* MemorNameEffect = StrNameEffect[settings.IdColorEffects]; //Змінна для запам'ятовування назви останього ефекту

char* StrNameOneColor[] = {"White", "Red", "Green", "Blue"};
char* MemorNameOneColor = StrNameOneColor[settings.IdOneColor];

uint8_t MasSettings[] = {20, 200};

float MemorBRIGHTNESS = 0;

byte MemorSpeedColorEffect;
byte MemorCountDisplayBRG;
boolean flagTEST = true;
// ================== SETUP ==================
void setup() {
  Serial.begin(115200);
  pinMode(BtnEnc, INPUT_PULLUP);
  encoder.setPosition(0);
  //delay(1000);
  tft.init(240, 320,SPI_MODE2);           // Init ST7789 320x240  // if using a 2.0" 320x240 TFT
  tft.fillScreen(ST77XX_BLACK);
  tft.invertDisplay(false);
 // tft.fillScreen(ST77XX_BLACK);
  tft.setRotation(1); //Horizontal   //1 and 3


  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(settings.BRIGHTNESS * 2.55);
  flagPassColorMode = true;

  //  EEPROM.begin(Size_EEPROM);
  //  EEPROM.get(1, settings);
  //  EEPROM.end();
  MemorSpeedColorEffect = 100 - settings.speedColorEffect;
  MemorBRIGHTNESS = settings.BRIGHTNESS * 2.55;
  MemorCountDisplayBRG = settings.CountDisplayBRG * 2.55;
  FastLED.setBrightness(MemorBRIGHTNESS);
  MemorNameMode = StrNameMode[settings.IdColorMode];
  MemorNameEffect = StrNameEffect[settings.IdColorEffects];
  MemorNameOneColor = StrNameOneColor[settings.IdOneColor];
  analogWriteFreq(500);
  analogWriteRange(255);
  analogWrite(12, MemorCountDisplayBRG);
//  tft.reset();
}

// ================== LOOP ==================
void loop() {
  //analogWrite(12, MemorCountDisplayBRG);
  //analogWrite(12, 150);
  if(flagTEST){
    flagTEST=false;
  }
  
  if (ee_request && millis() - ee_time > 3000) {
    ee_request = false;
    //    EEPROM.begin(Size_EEPROM);
    //    EEPROM.put(1, settings);
    //    EEPROM.end();
    //    Serial.println("Save_settings");
  }
  //flagPassTime = true;
//  if (flagPassTime) {
//    TimeCount();
//  }

  EncoderRead();  //Функція зчитування положення енкодера та стан його кнопки
  //drawtext("текст", колір, х кордината, y кордината, розмір тексту)

  //Виведення на екран інтерфейсів, кожна із ціх фунцій один із інтерфейсів
  switch (settings.IdMenu) {
    case 0: MMenu();
      break;
    case 1: MColor();
      break;
    case 2: MColorMode();
      break;
    case 3: MColorModeEffects();
      break;
    case 4: MColorModeOneColor();
      break;
    case 5: MColorBrightness();
      break;
    case 6: SpeedColorEffect();
      break;
    case 7: Settings();
      break;
    case 8: DisplayBRG();
      break;
  }

  if (settings.IdColorMode == 0) {
    FastLED.clear();
    FastLED.show();
  }

  //Виведення світлових ефектів. Зроблена спільна затримка, яка відповідаю за швидкість відтворення ефектів
  if (settings.IdColorMode == 2 && millis() - last_time > MemorSpeedColorEffect) {
    last_time = millis();
    switch (settings.IdColorEffects) {
      case 0: rainbow_fade();
        break;
      case 1: rainbow_loop();
        break;
      case 2: random_burst();
        break;
      case 3: color_bounce();
        break;
      case 4: color_bounceFADE();
        break;
      case 5: red_blue_bounce();
        break;
      case 6: rainbow();
        break;
    }
  }

  if (settings.IdColorMode == 1 && millis() - last_time > 50) {
    last_time = millis();
    switch (settings.IdOneColor) {
      case 0: updateColor(255, 225, 225); //White
        break;
      case 1: updateColor(255, 0, 0); //Red    //updateColor(uint8_t r,uint8_t g,uint8_t b)
        break;
      case 2: updateColor(0, 225, 0); //Green
        break;
      case 3: updateColor(0, 0, 225); //Blue
        break;
    }
  }
}

//Функція для виводу тексту на дисплей
void drawtext(String text, uint16_t color, int x, int y) {
  tft.setCursor(x, y); //(право,вниз)
  tft.setTextColor(color);
  tft.setTextSize(SizeText);
  tft.setTextWrap(true);
  tft.print(text);
}
//Функція для виводу вказівника на дисплей
void drawPointerMas(int newPos, uint8_t Mas[]) {
  if (memor != Mas[newPos]) {
    tft.setCursor(0, memor);
    tft.setTextColor(ST77XX_BLACK);
    tft.setTextSize(SizeText);
    tft.setTextWrap(true);
    tft.print(">");
  }
  tft.setCursor(0, Mas[newPos]);
  memor = Mas[newPos];
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(SizeText);
  tft.setTextWrap(true);
  tft.print(">");
}

void drawPointer(char *text , uint16_t color, int x, int y) {
  tft.setCursor(x, y);       //void drawPointer(char *text , uint16_t color,int x, int y)
  tft.setTextColor(color);   //ST77XX_BLACK
  tft.setTextSize(SizeText);
  tft.setTextWrap(true);
  tft.print(text);
}

//Функція зчитування положення енкодера та стан його кнопки
void EncoderRead() {
  encoder.tick();
  newPos = encoder.getPosition();   //призначення теперешнього положення енкодера до зміної
  //Обмеження для показника положення енкодера, POSMIN - мінімальне | POSMAX - максимальне положення
  if (newPos < POSMIN) {
    encoder.setPosition(POSMIN / STEPS);
    newPos = POSMIN;
  }
  else if (newPos > POSMAX) {
    encoder.setPosition(POSMAX / STEPS);
    newPos = POSMAX;
  }
  //Виведення позиції енкодера в serial port
  if (lastPos != newPos) {
    //Serial.println(newPos);
    lastPos = newPos;
    flagPassTime = true;
    flag = true; //Виконує роль шлюзу у фунції виведення інтерфейсів,
    //при перемиканні енкодера виконуються відкриття шлюзу, що забеспечує
    //однаразове оновлення інформації на дисплеї
//    if (Sec == 1)Sec = 0;
//    if (Sec == 10) {
//      //Sec = 0;
//      DisplaySleep("ON");
//      flagPassTime = true;
//    }
//     Sec = 0;
//     flagPassTime = false;
  }

  btn = !digitalRead(BtnEnc);  //Зчитування стану конопки енкодера
  //Блок відповідальний за однаразове спрацьовування дії при змінні стану кнопки
  if (btn == 1 && btnFlag == 0) {
    btnFlag = 1;
    Serial.println("Click");
  }
  if (btn == 0 && btnFlag == 1) {
    btnFlag = 0;
    PassFlag = 1;  ////Виконує роль шлюзу у фунції виведення інтерфейсів,
    //при змінні стану кнопки енкодеру (*не плутати із flag) виконуються відкриття шлюзу, що забеспечує
    //однаразове оновлення інформації на дисплеї
    Serial.println("ok");
  }
}

void SaveSettings() {
  ee_request = true;
  ee_time = millis();
  //Serial.println("ok");
}

void TimeCount() {
  if (millis() - time_work > 1000) {
    time_work = millis();
    Sec++;
    Serial.println(Sec);
    if (Sec >= 10) {
      DisplaySleep("OFF");
      flagPassTime = false;
    }
    //    if (Sec == 1) {
    //      DisplaySleep("ON");
    //    }
  }
}

void DisplaySleep(String state) {
  if (state == "OFF") {
    for (int i = MemorCountDisplayBRG; i >= 0; i = i - 1) {
      analogWrite(12, i);
    }
  }
  if (state == "ON") {
    for (int i = 0; i <= MemorCountDisplayBRG; i = i + 1) {
      analogWrite(12, i);
    }
  }
}

//Помітки =============================================================================
//Налаштування кординат інтерфейсу
//byte ModeX = 30, ModeY = 20;    //Mode
//byte MnmX = 130, MnmY = 20;     //MemorNameMode
////_____________________________________________
//byte MnfX = 40, MnfY = 50;      //MemorNameEffect
//byte MnoX = 40, MnoY = 50;      //MemorNameOneColor
////_____________________________________________
//byte BrgX = 30, BrgY = 100;      //Brightness
//byte BrgCX = 228, BrgCY = 100;   //Brightness Count
////_____________________________________________
//byte SdWX = 30, SdWY = 140;      //Speed work
//byte SdWCX = 228, SdWCY = 140;   //Speed work Count
////_____________________________________________
//byte BKX = 30, BKY = 200; //Back
