byte LED_COUNT = 17;
uint8_t idex = 0;                             //індекст теперешнього пікселя
float ihue = 0;                               // тон кольору
uint8_t saturationVal = 255;                  // насиченість
uint8_t ibright = 0;                          //значення яркості
uint16_t TOP_INDEX = uint8_t(LED_COUNT / 2);  // середина вірізку
uint8_t EVENODD = LED_COUNT % 2;              //флвг перевірки на чесність
uint8_t bouncedirection = 0;                  //флаг для color_bounce()
//uint8_t leds[LED_COUNT]; //масив для себереження випадкових значень пікселів
uint8_t stepValue = 50;
uint8_t hueValue = 0;
byte ST;

CRGBPalette16 currentPalette;
TBlendType currentBlending;

int db[] = { 5, 6, 4, 7, 3, 8, 2, 9, 1, 10, 0, 11, 15, 12, 14, 13,
             21, 22, 20, 23, 19, 24, 18, 25, 17, 26, 16, 27, 31, 28, 30, 29,
             33, 34, 32, 35, 47, 36, 46, 37, 45, 38, 44, 39, 43, 40, 42, 41 };

int da[] = { 5, 6, 7, 8, 9, 10, 11, 12,
             21, 20, 19, 18, 17, 16, 31, 30,
             33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 32,
             29, 28, 27, 26, 25, 24, 23, 22,
             13, 14, 15, 0, 1, 2, 3, 4 };

int dc[] = { 5, 6, 4, 7, 3, 8, 2, 9, 1, 10, 0, 11, 15, 12, 14, 13,
             21, 22, 20, 23, 19, 24, 18, 25, 17, 26, 16, 27, 31, 28, 30, 29,
             33, 34, 32, 35, 47, 36, 46, 37, 45, 38, 44, 39, 43, 40, 42, 41 };

uint8_t colorLoop = 1;

const TProgmemPalette16 MyColors_p PROGMEM = {
  CRGB::DarkBlue,
  CRGB::HotPink,
  CRGB::Teal,
  CRGB::BlueViolet,

  CRGB::DodgerBlue,
  CRGB::DeepPink,
  CRGB::Turquoise,
  CRGB::Indigo,

  CRGB::DarkBlue,
  CRGB::HotPink,
  CRGB::Teal,
  CRGB::BlueViolet,

  CRGB::DodgerBlue,
  CRGB::DeepPink,
  CRGB::Turquoise,
  CRGB::Indigo,
};


void updateColor(uint8_t HexColors) {
  for (uint8_t i = 0; i < LED_COUNT; i++) {
    leds[i] = testHex[HexColors];
  }
  LEDS.show();
}

void updateColorEffectFade(int HexC1, int HexC2, int HexC3, int HexC4){
  CRGB Clolor1 = HexC1;
  CRGB Clolor2 = HexC2;
  CRGB Clolor3 = HexC3;
  CRGB Clolor4 = HexC4;
  CRGB black = CRGB::Black;

  currentPalette = CRGBPalette16(
    Clolor1, Clolor1, Clolor1, Clolor1,
    Clolor2, Clolor2, Clolor2, Clolor2,
    Clolor3, Clolor3, Clolor3, Clolor3,
    Clolor4, Clolor4, Clolor4, Clolor4);
    //FillLEDsFromPaletteColors(startIndex);
}

void defTest() {    //8, 13, 48
  ST = 8;
  updateColorEffectFade(0xFF8787,0xF8C4B4,0xE5EBB2,0xBCE29E);
  FillLEDsFromPaletteColors(startIndex);
}

void Spring(){
  ST = 8;
  updateColorEffectFade(0xFF8787,0xF8C4B4,0xE5EBB2,0xBCE29E);
  FillLEDsFromPaletteColors(startIndex);
  //https://colorhunt.co/palette/ff8787f8c4b4e5ebb2bce29e
}

void Fall(){
  ST = 8;
  updateColorEffectFade(0xD06224,0xAE431E,0x8A8635,0xE9C891);
  FillLEDsFromPaletteColors(startIndex);
  //https://colorhunt.co/palette/d06224ae431e8a8635e9c891
}

void Summer(){
  ST = 8;
  updateColorEffectFade(0x2192FF,0x38E54D,0x9CFF2E,0xFDFF00);
  FillLEDsFromPaletteColors(startIndex);
  //https://colorhunt.co/palette/2192ff38e54d9cff2efdff00
}

void Winter(){
  ST = 8;
  updateColorEffectFade(0x06283D,0x256D85,0x47B5FF,0xDFF6FF);
  FillLEDsFromPaletteColors(startIndex);
  //https://colorhunt.co/palette/06283d256d8547b5ffdff6ff
}

void Coffe2(){
  ST = 8;
  updateColorEffectFade(0x402218,0x865439,0xC68B59,0xD7B19D);
  FillLEDsFromPaletteColors(startIndex);
  //https://colorhunt.co/palette/402218865439c68b59d7b19d
}

void Coffe1(){
  ST = 8;
  updateColorEffectFade(0x1C0A00,0x361500,0x603601,0xCC9544);
  FillLEDsFromPaletteColors(startIndex);
  //https://colorhunt.co/palette/1c0a00361500603601cc9544
}

void Nature2(){
  ST = 13;
  updateColorEffectFade(0xAC4425,0x224B0C,0xC1D5A4,0xF0F2B6);
  FillLEDsFromPaletteColors(startIndex);
  //https://colorhunt.co/palette/ac4425224b0cc1d5a4f0f2b6
}

void Nature1(){
  ST = 13;
  updateColorEffectFade(0xFED049,0xCFFDE1,0x68B984,0x3D5656);
  FillLEDsFromPaletteColors(startIndex);
  //https://colorhunt.co/palette/fed049cffde168b9843d5656
}

void Dark4(){
  ST = 13;
  updateColorEffectFade(0x382933,0x3B5249,0x519872,0x382933);
  FillLEDsFromPaletteColors(startIndex);
  //https://colorhunt.co/palette/3829333b5249519872a4b494
}

void Dark3(){
  ST = 13;
  updateColorEffectFade(0x161616,0x346751,0xC84B31,0x161616);
  FillLEDsFromPaletteColors(startIndex);
  //https://colorhunt.co/palette/161616346751c84b31ecdbba
}

void Dark2(){
  ST = 13;
  updateColorEffectFade(0x000000,0x150050,0x3F0071,0x150050);
  FillLEDsFromPaletteColors(startIndex);
  //https://colorhunt.co/palette/0000001500503f0071610094
}

void Dark1(){
  ST = 13;
  updateColorEffectFade(0x16213E,0x0F3460,0x533483,0x16213E);
  FillLEDsFromPaletteColors(startIndex);
  //https://colorhunt.co/palette/16213e0f3460533483e94560
}

void Neon3(){
  ST = 13;
  updateColorEffectFade(0x120078,0x9D0191,0xFD3A69,0xFECD1A);
  FillLEDsFromPaletteColors(startIndex);
  //https://colorhunt.co/palette/1200789d0191fd3a69fecd1a
}

void Neon2(){
  ST = 13;
  updateColorEffectFade(0xF7FD04,0xF9B208,0xF98404,0xFC5404);
  FillLEDsFromPaletteColors(startIndex);
  //https://colorhunt.co/palette/f7fd04f9b208f98404fc5404
}

void Neon1(){
  ST = 48;
  updateColorEffectFade(0x2E0249,0x570A57,0xA91079,0xF806CC);
  FillLEDsFromPaletteColors(startIndex);
  //https://colorhunt.co/palette/2e0249570a57a91079f806cc
}

void Retro6(){
  ST = 13;
  updateColorEffectFade(0x000000,0x1A4D2E,0xFF9F29,0xFAF3E3);
  FillLEDsFromPaletteColors(startIndex);
  //https://colorhunt.co/palette/0000001a4d2eff9f29faf3e3  
}

void Retro5(){
  ST = 13;
  updateColorEffectFade(0x006E7F,0xF8CB2E,0xEE5007,0xB22727);
  FillLEDsFromPaletteColors(startIndex);
  //https://colorhunt.co/palette/006e7ff8cb2eee5007b22727
}

void Retro4(){
  ST = 13;
  updateColorEffectFade(0x11052C,0x3D087B,0xF43B86,0xFFE459);
  FillLEDsFromPaletteColors(startIndex);
  //https://colorhunt.co/palette/11052c3d087bf43b86ffe459
}

void Retro3(){ 
  ST = 13;
  updateColorEffectFade(0x96CEB4,0xFFEEAD,0xD9534F,0xFFAD60);
  FillLEDsFromPaletteColors(startIndex);
  //https://colorhunt.co/palette/96ceb4ffeeadd9534fffad60
}

void Retro2(){ 
  ST = 48;
  updateColorEffectFade(0xF3EFE0,0x434242,0x222222,0x22A39F);
  FillLEDsFromPaletteColors(startIndex);
  //https://colorhunt.co/palette/f3efe043424222222222a39f
}

void Retro1(){ 
  ST = 8;
  updateColorEffectFade(0x10A19D,0x540375,0xFF7000,0xFFBF00);
  FillLEDsFromPaletteColors(startIndex);
  //https://colorhunt.co/palette/10a19d540375ff7000ffbf00
}

void rainbow_fade() {
  ihue = ihue + 0.25;
  if (ihue > 255) {
    ihue = 0;
  }
  for (int idex = 0; idex < LED_COUNT; idex++) {  //переробити під соті float//
    leds[idex] = CHSV(ihue, saturationVal, 255);
  }
}

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
}

void random_burst() {
  idex = random(0, LED_COUNT);
  ihue = random(0, 255);
  leds[idex] = CHSV(ihue, saturationVal, 255);
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
  for (int i = 0; i < LED_COUNT; i++) {
    if (i == idex) {
      leds[i] = CHSV(hueValue, saturationVal, 255);
    } else {
      leds[i] = CHSV(0, 0, 0);
    }
  }
}

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

  for (int i = 0; i < LED_COUNT; i++) {
    if (i == idex) {
      leds[i] = CHSV(hueValue, saturationVal, 255);
    } else if (i == iL1) {
      leds[i] = CHSV(hueValue, saturationVal, 150);
    } else if (i == iL2) {
      leds[i] = CHSV(hueValue, saturationVal, 80);
    } else if (i == iL3) {
      leds[i] = CHSV(hueValue, saturationVal, 20);
    } else if (i == iR1) {
      leds[i] = CHSV(hueValue, saturationVal, 150);
    } else if (i == iR2) {
      leds[i] = CHSV(hueValue, saturationVal, 80);
    } else if (i == iR3) {
      leds[i] = CHSV(hueValue, saturationVal, 20);
    } else {
      leds[i] = CHSV(0, 0, 0);
    }
  }
  LEDS.show();
}

void red_blue_bounce() {
  idex++;
  if (idex >= LED_COUNT) {
    idex = 0;
  }
  int idexR = idex;
  int idexB = antipodal_index(idexR);
  int thathue = (hueValue + 160) % 255;

  for (int i = 0; i < LED_COUNT; i++) {
    if (i == idexR) {
      leds[i] = CHSV(hueValue, saturationVal, 255);
    } else if (i == idexB) {
      leds[i] = CHSV(thathue, saturationVal, 255);
    } else {
      leds[i] = CHSV(0, 0, 0);
    }
  }
}

void rainbow() {
  EVERY_N_MILLISECONDS(20) {
    gHue++;
  }
  fill_rainbow(leds, NUM_LEDS, gHue, 7);
}

void rainbow2() {
  currentPalette = RainbowColors_p;
  ST = 8;
  FillLEDsFromPaletteColors(startIndex);
}

void rainbowSC() {
  currentPalette = RainbowStripeColors_p;
  ST = 8;
  currentBlending = NOBLEND;
  FillLEDsFromPaletteColors(startIndex);
}

void partyColors() {
  currentPalette = PartyColors_p;
  ST = 48;
  currentBlending = LINEARBLEND;
  FillLEDsFromPaletteColors(startIndex);
}

void MyColors() {
  currentPalette = MyColors_p;
  ST = 48;
  FillLEDsFromPaletteColors(startIndex);
}

void HeatColors() {
  currentPalette = HeatColors_p;
  ST = 11;
  FillLEDsFromPaletteColors(startIndex);
}

void Watermelon() {
  SetupWatermelonPalette();
  ST = 8;
  FillLEDsFromPaletteColors(startIndex);
}

void ForestColors() {
  currentPalette = ForestColors_p;
  ST = 48;
  FillLEDsFromPaletteColors(startIndex);
}

void OceanColors() {
  currentPalette = OceanColors_p;
  ST = 8;
  FillLEDsFromPaletteColors(startIndex);
}

void NOBLEND_P() {
  SetupNewPalette();
  ST = 16;
  currentBlending = NOBLEND;
  FillLEDsFromPaletteColors(startIndex);
}

void LavaColors() {
  currentPalette = LavaColors_p;
  ST = 8;
  FillLEDsFromPaletteColors(startIndex);
}

void CloudColors() {
  currentPalette = CloudColors_p;
  ST = 8;
  FillLEDsFromPaletteColors(startIndex);
}

void BMR() {
  animationA();                 // render the first animation into leds2
  animationB();                 // render the second animation into leds3
  uint8_t ratio = beatsin8(2);  // Alternate between 0 and 255 every minute

  for (int i = 0; i < NUM_LEDS; i++) {  // mix the 2 arrays together
    leds[dc[i]] = blend(leds2[dc[i]], leds3[dc[i]], ratio);
  }
}

void BMR2() {
  //animationA();                                               // render the first animation into leds2
  animationB();                 // render the second animation into leds3
  uint8_t ratio = beatsin8(2);  // Alternate between 0 and 255 every minute

  for (int i = 0; i < NUM_LEDS; i++) {  // mix the 2 arrays together
    leds[dc[i]] = blend(leds2[dc[i]], leds3[dc[i]], ratio);
  }
}

void BMR3() {
  animationA();  // render the first animation into leds2
  //animationB();                                               // render the second animation into leds3
  uint8_t ratio = beatsin8(2);  // Alternate between 0 and 255 every minute

  for (int i = 0; i < NUM_LEDS; i++) {  // mix the 2 arrays together
    leds[dc[i]] = blend(leds2[dc[i]], leds3[dc[i]], ratio);
  }
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
  } else {
    r = LED_COUNT - 1;
  }
  return r;
}

int antipodal_index(int i) {
  int iN = i + TOP_INDEX;
  if (i >= TOP_INDEX) {
    iN = (i + TOP_INDEX) % LED_COUNT;
  }
  return iN;
}

void FillLEDsFromPaletteColors(uint8_t colorIndex) {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[da[i]] = ColorFromPalette(currentPalette, colorIndex, MemorBRIGHTNESS, currentBlending);
    colorIndex += ST;
  }
}

void SetupNewPalette() {
  fill_solid(currentPalette, 16, CRGB::Black);
  //  set half of the LEDs to the color selected here
  //  Play with the color, steps, and speed to get different results.
  currentPalette[0] = CRGB::DodgerBlue;
  currentPalette[1] = CRGB::DodgerBlue;
  currentPalette[2] = CRGB::DodgerBlue;
  currentPalette[3] = CRGB::DodgerBlue;

  currentPalette[8] = CRGB::DodgerBlue;
  currentPalette[9] = CRGB::DodgerBlue;
  currentPalette[10] = CRGB::DodgerBlue;
  currentPalette[11] = CRGB::DodgerBlue;
}
//  This function sets up a palette of purple and green stripes.
//  Play with the color, steps, and speed to get different results.
void SetupWatermelonPalette() {  //Kavynna BAZA!!!
  CRGB Green = CHSV(HUE_GREEN, 255, 255);
  CRGB Pink = CHSV(HUE_PINK, 255, 255);
  CRGB black = CRGB::Black;

  currentPalette = CRGBPalette16(
    Green, Green, Green, Green,
    Pink, Pink, Pink, Pink,
    Green, Green, Green, Green,
    Pink, Pink, Pink, Pink);
}

void SlavaUkraini() {
  ST = 8;
  updateColorEffectFade(0x0000FF,0xFFFF00,0x0000FF,0xFFFF00);
  FillLEDsFromPaletteColors(startIndex);
}

void animationA() {  // running red stripe.

  for (int i = 0; i < NUM_LEDS; i++) {
    uint8_t red = (millis() / 5) + (i * 12);  // speed, length
    if (red > 128) red = 0;
    leds2[dc[i]] = CRGB(red, 0, 0);
  }
}  // animationA()

void animationB() {  // running blue stripe in opposite direction.

  for (int i = 0; i < NUM_LEDS; i++) {
    uint8_t blue = (millis() / 5) - (i * 12);  // speed, length
    if (blue > 128) blue = 0;
    leds3[dc[i]] = CRGB(0, 0, blue);
  }
}  // animationB()

// void copy(int* src, int* dst, int len) {
//     memcpy(dst, src, sizeof(src[0])*len);
// }



// CRGB Clolor1 = CHSV(HUE_ORANGE, 255, 255);
//   CRGB Clolor2 = CHSV(HUE_PURPLE, 255, 255);
//   CRGB Clolor3 = CHSV(HUE_ORANGE, 255, 255);
//   CRGB Clolor4 = CHSV(HUE_PURPLE, 255, 255);
//   CRGB black = CRGB::Black;

//   currentPalette = CRGBPalette16(
//     Clolor1, Clolor1, Clolor1, Clolor1,
//     Clolor2, Clolor2, Clolor2, Clolor2,
//     Clolor3, Clolor3, Clolor3, Clolor3,
//     Clolor4, Clolor4, Clolor4, Clolor4);


  // CRGB Clolor1 = 0x10A19D;
  // CRGB Clolor2 = CRGB(0, 0, 0);
  // CRGB Clolor3 = CRGB(255, 112, 0);
  // CRGB Clolor4 = CRGB(0, 0, 0);
  // CRGB black = CRGB::Black;
