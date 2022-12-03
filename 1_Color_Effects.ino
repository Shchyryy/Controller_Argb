byte LED_COUNT = 17;
uint8_t idex = 0; //індекст теперешнього пікселя
float ihue = 0; // тон кольору
uint8_t saturationVal = 255; // насиченість
uint8_t ibright = 0; //значення яркості
uint16_t TOP_INDEX = uint8_t(LED_COUNT / 2); // середина вірізку
uint8_t EVENODD = LED_COUNT % 2; //флвг перевірки на чесність
uint8_t bouncedirection = 0; //флаг для color_bounce()
//uint8_t leds[LED_COUNT]; //масив для себереження випадкових значень пікселів
uint8_t stepValue = 50;
uint8_t hueValue = 0;


void updateColor(uint8_t HexColors) { //Pro mode
  for (uint8_t i = 0 ; i < LED_COUNT; i++ ) {
    leds[i] = testHex[HexColors];
    Serial.println(HexColors);
  }
  LEDS.show();
}



//плавная смена цветов
void rainbow_fade() {
  ihue = ihue + 0.25;
  if (ihue > 255) {
    ihue = 0;
  }
  for (int idex = 0 ; idex < LED_COUNT; idex++ ) { //переробити під соті float//
    leds[idex] = CHSV(ihue, saturationVal, 255);
  }
  LEDS.show();
}

// крутящаяся радуга
void rainbow_loop() {
  idex++;
  ihue = ihue + stepValue;
  if (idex >= LED_COUNT) {
    idex = 0;
  }
  if (ihue > 255) {
    ihue = 0;
  }
  leds[idex] = CHSV(ihue, saturationVal, 255);
  LEDS.show();
}

// случайная смена цветов
void random_burst() {
  idex = random(0, LED_COUNT);
  ihue = random(0, 255);
  leds[idex] = CHSV(ihue, saturationVal, 255);
  LEDS.show();
}

void color_bounce() {
  if (bouncedirection == 0) {
    idex = idex + 1;
    if (idex == LED_COUNT) {
      bouncedirection = 1;
      idex = idex - 1;
    }
  }
  if (bouncedirection == 1) {
    idex = idex - 1;
    if (idex == 0) {
      bouncedirection = 0;
    }
  }
  for (int i = 0; i < LED_COUNT; i++ ) {
    if (i == idex) {
      leds[i] = CHSV(hueValue, saturationVal, 255);
    }
    else {
      leds[i] = CHSV(0, 0, 0);
    }
  }
  LEDS.show();
}

//бегающий паровозик пикселей
void color_bounceFADE() {
  if (bouncedirection == 0) {
    idex = idex + 1;
    if (idex == LED_COUNT) {
      bouncedirection = 1;
      idex = idex - 1;
    }
  }
  if (bouncedirection == 1) {
    idex = idex - 1;
    if (idex == 0) {
      bouncedirection = 0;
    }
  }
  int iL1 = adjacent_cw(idex);
  int iL2 = adjacent_cw(iL1);
  int iL3 = adjacent_cw(iL2);
  int iR1 = adjacent_ccw(idex);
  int iR2 = adjacent_ccw(iR1);
  int iR3 = adjacent_ccw(iR2);

  for (int i = 0; i < LED_COUNT; i++ ) {
    if (i == idex) {
      leds[i] = CHSV(hueValue, saturationVal, 255);
    }
    else if (i == iL1) {
      leds[i] = CHSV(hueValue, saturationVal, 150);
    }
    else if (i == iL2) {
      leds[i] = CHSV(hueValue, saturationVal, 80);
    }
    else if (i == iL3) {
      leds[i] = CHSV(hueValue, saturationVal, 20);
    }
    else if (i == iR1) {
      leds[i] = CHSV(hueValue, saturationVal, 150);
    }
    else if (i == iR2) {
      leds[i] = CHSV(hueValue, saturationVal, 80);
    }
    else if (i == iR3) {
      leds[i] = CHSV(hueValue, saturationVal, 20);
    }
    else {
      leds[i] = CHSV(0, 0, 0);
    }
  }
  LEDS.show();
}

// вращение красного и синего
void red_blue_bounce() {
  idex++;
  if (idex >= LED_COUNT) {
    idex = 0;
  }
  int idexR = idex;
  int idexB = antipodal_index(idexR);
  int thathue = (hueValue + 160) % 255;

  for (int i = 0; i < LED_COUNT; i++ ) {
    if (i == idexR) {
      leds[i] = CHSV(hueValue, saturationVal, 255);
    }
    else if (i == idexB) {
      leds[i] = CHSV(thathue, saturationVal, 255);
    }
    else {
      leds[i] = CHSV(0, 0, 0);
    }
  }
  LEDS.show();
}

void rainbow()
{
  EVERY_N_MILLISECONDS( 20 ) {
    gHue++;
  }
  fill_rainbow( leds, NUM_LEDS, gHue, 7);
  LEDS.show();
}


int adjacent_cw(int i) {
  int r;
  if (i < LED_COUNT - 1) {
    r = i + 1;
  } else {
    r = 0;
  }
  return r;
}
int adjacent_ccw(int i) {
  int r;
  if (i > 0) {
    r = i - 1;
  }
  else {
    r = LED_COUNT - 1;
  }
  return r;
}

int antipodal_index(int i) {
  int iN = i + TOP_INDEX;
  if (i >= TOP_INDEX) {
    iN = ( i + TOP_INDEX ) % LED_COUNT;
  }
  return iN;
}
