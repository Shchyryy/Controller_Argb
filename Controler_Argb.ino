// ================== LIBS ==================
#include <Arduino.h>
#include <Adafruit_GFX.h>     // Core graphics library
#include <Adafruit_ST7735.h>  // Hardware-specific library for ST7735
#include <Adafruit_ST7789.h>  // Hardware-specific library for ST7789
#include <SPI.h>
#include "RotaryEncoder.h"
#include <FastLED.h>
#include <EEPROM.h>
#include "colorutils.h"
#include "colorpalettes.h"
#include "string.h"
#include <pixeltypes.h>

//defined (TFT 2.8 ESP8266) ======
#define TFT_CS 4
#define TFT_RST 0
#define TFT_DC 2

//defined FastLed ================
#define DATA_PIN 15
#define LED_TYPE WS2812
#define COLOR_ORDER GRB
#define NUM_STRIPS 3
#define NUM_LEDS_PER_STRIP 16
#define NUM_LEDS NUM_LEDS_PER_STRIP* NUM_STRIPS
#define FRAMES_PER_SECOND 120

//defined Encoder ================
byte STEPS = 1;
#define BtnEnc 3
#define LedDisplay 12

// ================== OBJECTS ==================
RotaryEncoder encoder(16, 5, RotaryEncoder::LatchMode::FOUR3);
// For 1.14", 1.3", 1.54", 1.69", and 2.0" TFT with ST7789:
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);


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
unsigned long testTm;

unsigned long ee_time;
boolean ee_request = false;
byte Size_EEPROM = 10;  // змінив, було 6

int Sec;

struct {
  byte IdMenu = 0;
  byte IdColorMode = 0;
  byte IdColorEffects = 0;
  byte IdOneColor = 0;
  byte BRIGHTNESS = 80;
  byte speedColorEffect = 80;
  byte CountDisplayBRG = 100;
  byte CountTimeSleepDisplay = 0;
} settings;

uint8_t MasMenu[] = { 90, 120, 100 };  //20/60/100/140/180|  Масив відповідальний за положення вказівника, та за переміщення по меню
uint8_t MasColor[] = { 20, 200 };      //Масив відповідальний за положення вказівника, та за переміщення по під меню "Color"
char* StrNameMode[] = { "Off", "One color", "Effects" };
char* MemorNameMode = StrNameMode[settings.IdColorMode];

char* StrNameEffect[] = { "rainbow_fade|", "rainbow|", "rainbow2|", "rainbow_loop|", "random_burst|", "rainbowSC|", "partyColors|",
                          "Pastel|", "HeatColors|", "Slava Ukraini|", "Kavun baza|", "ForestColors|", "OceanColors|", "NOBLEND_P|", "LavaColors|", "CloudColors|", "BMR|", "BMR2|", "BMR3|",
                          "Winter|", "Spring|", "Summer|", "Fall|", "Coffe1|", "Coffe2|", "Nature1|", "Nature2|", "Dark1|", "Dark2|", "Dark3|", "Dark4|", "Neon1|", "Neon2|", "Neon3|", "Retro1|", "Retro2|",
                          "Retro3|", "Retro4|", "Retro5|", "Retro6|" };
//Масив відповідальний за назву ефектів, для подальшого виведення іх на дисплей
char* MemorNameEffect = StrNameEffect[settings.IdColorEffects];  //Змінна для запам'ятовування назви останього ефекту

char* StrNameOneColor[] = { "white", "red", "lime", "blue", "yellow", "cyan", "magenta", "silver", "gray", "maroon", "olive", "green",
                            "purple", "teal", "navy", "dark red", "brown", "firebrick", "crimson", "tomato", "coral", "indian red", "light coral",
                            "dark salmon", "salmon", "light salmon", "orange red", "dark orange", "orange", "gold", "d golden rod", "golden rod", "p golden rod",
                            "dark khaki", "khaki", "yellow green", "d olive green", "olive drab", "lawn green", "chartreuse", "green yellow",
                            "dark green", "forest green", "lime green", "light green", "pale green", "d sea green", "m spring green",
                            "spring green", "sea green", "aqua marine", "sea green", "l sea green", "d slate gray", "dark cyan", "aqua",
                            "light cyan", "d turquoise", "turquoise", "m turquoise", "p turquoise", "aqua marine", "powder blue", "cadet blue",
                            "steel blue", "flower blue", "deep sky blue", "dodger blue", "light blue", "sky blue", "light sky blue", "midnight blue",
                            "dark blue", "medium blue", "royal blue", "blue violet", "indigo", "d slate blue", "slate blue", "m slate blue",
                            "medium purple", "dark magenta", "dark violet", "dark orchid", "medium orchid", "thistle", "plum", "violet", "orchid",
                            "m violet red", "violet red", "deep pink", "hot pink", "light pink", "pink", "antique white", "beige", "bisque", "almond",
                            "wheat", "corn silk", "lemon chiffon", "light golden", "light yellow", "saddle brown", "sienna", "chocolate", "peru", "sandy brown",
                            "burly wood", "tan", "rosy brown", "moccasin", "navajo white", "peach puff", "misty rose", "lavender blush", "linen", "old lace", "papaya whip",
                            "sea shell", "mint cream", "slate gray", "slate gray", "steel blue", "lavender", "floral white", "alice blue", "ghost white",
                            "honeydew", "ivory", "azure", "snow", "dim gray", "dark gray ", "light gray", "gainsboro", "white smoke" };

int testHex[] = { 0xFFFFFF, 0xFF0000, 0x00FF00, 0x0000FF, 0xFFFF00, 0x00FFFF, 0xFF00FF, 0xC0C0C0, 0x808080, 0x800000, 0x808000, 0x008000,
                  0x800080, 0x008080, 0x000080, 0x8B0000, 0xA52A2A, 0xB22222, 0xDC143C, 0xFF6347, 0xFF7F50, 0xCD5C5C, 0xF08080, 0xE9967A, 0xFA8072,
                  0xFFA07A, 0xFF4500, 0xFF8C00, 0xFFA500, 0xFFD700, 0xB8860B, 0xDAA520, 0xEEE8AA, 0xBDB76B, 0xF0E68C, 0x9ACD32, 0x556B2F,
                  0x6B8E23, 0x7CFC00, 0x7FFF00, 0xADFF2F, 0x006400, 0x228B22, 0x32CD32, 0x90EE90, 0x98FB98, 0x8FBC8F, 0x00FA9A, 0x00FF7F,
                  0x2E8B57, 0x66CDAA, 0x3CB371, 0x20B2AA, 0x2F4F4F, 0x008B8B, 0x00FFFF, 0x00FFFF, 0xE0FFFF, 0x00CED1, 0x40E0D0, 0x48D1CC, 0xAFEEEE,
                  0x7FFFD4, 0xB0E0E6, 0x5F9EA0, 0x4682B4, 0x6495ED, 0x00BFFF, 0x1E90FF, 0xADD8E6, 0x87CEEB, 0x87CEFA, 0x191970, 0x00008B, 0x0000CD,
                  0x4169E1, 0x8A2BE2, 0x4B0082, 0x483D8B, 0x6A5ACD, 0x7B68EE, 0x9370DB, 0x8B008B, 0x9400D3, 0x9932CC, 0xBA55D3, 0xD8BFD8,
                  0xDDA0DD, 0xEE82EE, 0xDA70D6, 0xC71585, 0xDB7093, 0xFF1493, 0xFF69B4, 0xFFB6C1, 0xFFC0CB, 0xFAEBD7, 0xF5F5DC, 0xFFE4C4, 0xFFEBCD,
                  0xF5DEB3, 0xFFF8DC, 0xFFFACD, 0xFAFAD2, 0xFFFFE0, 0x8B4513, 0xA0522D, 0xD2691E, 0xCD853F, 0xF4A460, 0xDEB887, 0xD2B48C, 0xBC8F8F, 0xFFE4B5,
                  0xFFDEAD, 0xFFDAB9, 0xFFE4E1, 0xFFF0F5, 0xFAF0E6, 0xFDF5E60, 0xFFEFD5, 0xFFF5EE, 0xF5FFFA, 0x708090, 0x778899, 0xB0C4DE, 0xE6E6FA, 0xFFFAF0,
                  0xF0F8FF, 0xF8F8FF, 0xF0FFF0, 0xFFFFF0, 0xF0FFFF, 0xFFFAFA, 0x696969, 0xA9A9A9, 0xD3D3D3, 0xDCDCDC, 0xF5F5F5 };

char* MemorNameOneColor = StrNameOneColor[settings.IdOneColor];

uint8_t MasSettings[] = { 20, 55, 90, 125, 200 };

char* TimeSleepDisplay[] = { "Off", "15c", "30c", "1m", "2m", "5m", "10m" };
int timeSleep = 0;
float MemorBRIGHTNESS = 0;

byte MemorSpeedColorEffect;
byte MemorCountDisplayBRG;

static uint8_t startIndex = 0;

CRGB leds2[NUM_LEDS];
CRGB leds3[NUM_LEDS];

int i = 0;

// ================== SETUP ==================
void setup() {
  //delay(2000);
  Serial.begin(115200);
  pinMode(BtnEnc, INPUT_PULLUP);
  pinMode(LedDisplay, OUTPUT);
  encoder.setPosition(0);
  //delay(1000);
  tft.init(240, 320, SPI_MODE2);  // Init ST7789 320x240  // if using a 2.0" 320x240 TFT
  tft.fillScreen(ST77XX_BLACK);
  tft.invertDisplay(false);
  // tft.fillScreen(ST77XX_BLACK);
  tft.setRotation(3);  //Horizontal   //1 and 3

  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  flagPassColorMode = true;

  // if (EEPROM.read(0) != "n") {
  //   //EEPROM.begin(Size_EEPROM);
  //   EEPROM.put(1, settings);
  //   EPPROM.write(0, "n");
  //   EEPROM.end();
  // }
  // else {
  //EEPROM.begin(Size_EEPROM);
  // }

  EEPROM.begin(Size_EEPROM);
  EEPROM.get(1, settings);
  EEPROM.end();

  MemorSpeedColorEffect = 100 - settings.speedColorEffect;
  MemorBRIGHTNESS = settings.BRIGHTNESS * 2.55;
  MemorCountDisplayBRG = settings.CountDisplayBRG * 2.55;
  //FastLED.setBrightness(MemorBRIGHTNESS);
  MemorNameMode = StrNameMode[settings.IdColorMode];
  MemorNameEffect = StrNameEffect[settings.IdColorEffects];
  MemorNameOneColor = StrNameOneColor[settings.IdOneColor];
  analogWriteFreq(500);
  analogWriteRange(255);
  //analogWrite(LedDisplay, MemorCountDisplayBRG);

  // for (int i = 0; i <= MemorCountDisplayBRG; i++) {
  //   Serial.println(i);
  //   analogWrite(LedDisplay, i);
  // }
}

// ================== LOOP ==================
void loop() {

  //Serial.println(encoder.getPosition());
  TimeCount();
  SleepDisplay();

  if (ee_request && millis() - ee_time > 10000) {
    ee_request = false;
    EEPROM.begin(Size_EEPROM);
    EEPROM.put(1, settings);
    EEPROM.end();
    Serial.println("Save_settings");
  }

  EncoderRead();  //Функція зчитування положення енкодера та стан його кнопки
  //drawtext("текст", колір, х кордината, y кордината, розмір тексту)

  //Виведення на екран інтерфейсів, кожна із ціх фунцій один із інтерфейсів
  switch (settings.IdMenu) {
    case 0:
      MMenu();
      break;
    case 1:
      MColor();
      break;
    case 2:
      MColorMode();
      break;
    case 3:
      MColorModeEffects();
      break;
    case 4:
      MColorModeOneColor();
      break;
    case 5:
      MColorBrightness();
      break;
    case 6:
      SpeedColorEffect();
      break;
    case 7:
      Settings();
      break;
    case 8:
      DisplayBRG();
      break;
    case 9:
      AutohorMenu();
      break;
    case 10:
      SleepDispMenu();
      break;
    case 11:
      FactoryResetMenu();
  }

  if (settings.IdColorMode == 0) {
    FastLED.clear();
    FastLED.show();
  }

  //Serial.println(newPos);

  //Виведення світлових ефектів. Зроблена спільна затримка, яка відповідаю за швидкість відтворення ефектів
  if (settings.IdColorMode == 2 && millis() - last_time > MemorSpeedColorEffect) {
    last_time = millis();
    startIndex = startIndex + 1;
    switch (settings.IdColorEffects) {
      case 0:
        rainbow_fade();
        //defTest();
        break;
      case 1:
        rainbow();
        break;
      case 2:
        rainbow2();
        break;
      case 3:
        rainbow_loop();
        break;
      case 4:
        random_burst();
        break;
      case 5:
        rainbowSC();
        break;
      case 6:
        partyColors();
        break;
      case 7:
        MyColors();
        break;
      case 8:
        HeatColors();
        break;
      case 9:
        SlavaUkraini();
        break;
      case 10:
        Watermelon();
        break;
      case 11:
        ForestColors();
        break;
      case 12:
        OceanColors();
        break;
      case 13:
        NOBLEND_P();
        break;
      case 14:
        LavaColors();
        break;
      case 15:
        CloudColors();
        break;
      case 16:
        BMR();
        break;
      case 17:
        BMR2();
        break;
      case 18:
        BMR3();
        break;
      case 19:
        Winter();
        break;
      case 20:
        Spring();
        break;
      case 21:
        Summer();
        break;
      case 22:
        Fall();
        break;
      case 23:
        Coffe1();
        break;
      case 24:
        Coffe2();
        break;
      case 25:
        Nature1();
        break;
      case 26:
        Nature2();
        break;
      case 27:
        Dark1();
        break;
      case 28:
        Dark2();
        break;
      case 29:
        Dark3();
        break;
      case 30:
        Dark4();
        break;
      case 31:
        Neon1();
        break;
      case 32:
        Neon2();
        break;
      case 33:
        Neon3();
        break;
      case 34:
        Retro1();
        break;
      case 35:
        Retro2();
        break;
      case 36:
        Retro3();
        break;
      case 37:
        Retro4();
        break;
      case 38:
        Retro5();
        break;
      case 39:
        Retro6();
        break;
    }
    LEDS.show();
  }

  if (settings.IdColorMode == 1 && millis() - last_time > 50) {
    last_time = millis();
    updateColor(settings.IdOneColor);
  }

  //Плане включення підсвітки та дисплею
  if (flagPassTime && millis() - time_work > 5) {
    time_work = millis();
    if (i <= MemorCountDisplayBRG) {
      analogWrite(LedDisplay, i);
    }
    if (i <= MemorBRIGHTNESS) {
      FastLED.setBrightness(i);
    }
    if (i == 255) {
      flagPassTime = false;
      //i = 0;
    }
    i++;
  }
}


//Функція для виводу тексту на дисплей
void drawtext(String text, uint16_t color, int x, int y, byte size = SizeText) {
  tft.setCursor(x, y);  //(право,вниз)
  tft.setTextColor(color);
  tft.setTextSize(size);
  tft.setTextWrap(true);
  tft.print(text);
}
//Функція для виводу вказівника на дисплей
void drawPointerMas(int newPos, uint8_t Mas[], int y = 0) {
  if (memor != Mas[newPos]) {
    tft.setCursor(y, memor);
    tft.setTextColor(ST77XX_BLACK);
    tft.setTextSize(SizeText);
    tft.setTextWrap(true);
    tft.print(">");
  }
  tft.setCursor(y, Mas[newPos]);
  memor = Mas[newPos];
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(SizeText);
  tft.setTextWrap(true);
  tft.print(">");
}

void drawPointer(char* text, uint16_t color, int x, int y, byte size = SizeText) {
  tft.setCursor(x, y);      //void drawPointer(char *text , uint16_t color,int x, int y)
  tft.setTextColor(color);  //ST77XX_BLACK
  tft.setTextSize(size);
  tft.setTextWrap(true);
  tft.print(text);
}

//Функція зчитування положення енкодера та стан його кнопки
int n;
int m = MemorCountDisplayBRG;
void EncoderRead() {
  encoder.tick();
  newPos = encoder.getPosition();  //призначення теперешнього положення енкодера до зміної

  //Обмеження для показника положення енкодера, POSMIN - мінімальне | POSMAX - максимальне положення
  if (newPos < POSMIN) {
    newPos = POSMIN;
    encoder.setPosition(POSMIN);
    UnSleepDisplay();
  } else if (newPos > POSMAX) {
    newPos = POSMAX;
    encoder.setPosition(POSMAX);
    UnSleepDisplay();
  }
  //Виведення позиції енкодера в serial port
  if (lastPos != newPos) {
    //Serial.println(encoder.getPosition(););
    UnSleepDisplay();
    lastPos = newPos;
    //flagPassTime = true;
    flag = true;  //Виконує роль шлюзу у фунції виведення інтерфейсів,
    //при перемиканні енкодера виконуються відкриття шлюзу, що забеспечує
    //однаразове оновлення інформації на дисплеї
  }

  btn = !digitalRead(BtnEnc);  //Зчитування стану конопки енкодера
  //Блок відповідальний за однаразове спрацьовування дії при змінні стану кнопки

  if (btn == 1 && btnFlag == 0) {
    btnFlag = 1;
    Serial.println("Click");
    UnSleepDisplay();
  }
  if (btn == 0 && btnFlag == 1) {
    btnFlag = 0;
    PassFlag = 1;  ////Виконує роль шлюзу у фунції виведення інтерфейсів,
    //при змінні стану кнопки енкодеру (*не плутати із flag) виконуються відкриття шлюзу, що забеспечує
    //однаразове оновлення інформації на дисплеї
    time_work = 0;
  }
}

void SaveSettings() {
  ee_request = true;
  ee_time = millis();
  //Serial.println("ok");
}

void SleepDisplay() {
  //Serial.println(Sec - n);
  if (timeSleep != 0 && Sec - n >= timeSleep) {
    if (m > 0) {
      m--;
      analogWrite(LedDisplay, m);
      //Serial.println(m);
    }
  }
}

void UnSleepDisplay() {  //конфліктує із налаштуванням яскравості
  n = Sec;
  m = MemorCountDisplayBRG;
  analogWrite(LedDisplay, m);
}

void TimeCount() {
  if (millis() - testTm > 1000) {
    testTm = millis();
    Sec++;
    //Serial.println(Sec);
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
