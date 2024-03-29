
//Функція відповідальна за виведення на дислей "Menu"
void MMenu() {
  //Setting MMenu
  POSMIN = 0;
  POSMAX = 1;
  //===============

  if (flag == true) {
    //drawtext("==============", ST77XX_WHITE, 30, 40);
    drawtext("|  Color   |", ST77XX_WHITE, 50, 90);  // ( право, вниз )
    drawtext("|  Setting |", ST77XX_WHITE, 50, 120);
    //drawtext("==============", ST77XX_WHITE, 30, 170);
    drawPointerMas(newPos, MasMenu, 70);
    flag = false;
  }

  if (PassFlag) {
    PassFlag = 0;
    switch (MasMenu[newPos]) {
      case 90:
        ClearMenu();
        settings.IdMenu = 1;
        flag = true;
        newPos = 0;
        encoder.setPosition(0);
        flagPassColorMode = true;
        drawPointer(">", ST77XX_BLACK, 70, 90);
        break;
      case 120:
        ClearMenu();
        flag = true;
        newPos = 0;
        encoder.setPosition(0);
        settings.IdMenu = 7;
        drawPointer(">", ST77XX_BLACK, 70, 120);
        break;
      case 100:
        break;
    }
  }
}

//Функція відповідальна за виведення на дислей під меню "Color"
void MColor() {
  //Setting MColor
  POSMIN = 0;
  //===============

  if (flag == true) {
    flag = false;
    drawtext("Mode: ", ST77XX_WHITE, 30, 20);
    drawtext(MemorNameMode, ST77XX_WHITE, 130, 20);

    if (MemorNameMode == "Effects") {
      drawtext(MemorNameEffect, ST77XX_WHITE, 40, 50);
      drawtext("Brightness:" + (String)settings.BRIGHTNESS, ST77XX_WHITE, 30, 100);
      drawtext("Speed work:" + (String)settings.speedColorEffect, ST77XX_WHITE, 30, 140);
      drawtext("______________", ST77XX_BLUE, 30, 70);
      drawtext("______________", ST77XX_YELLOW, 30, 155);
      POSMAX = 4;
      MasColor[1] = 50;
      MasColor[2] = 100;
      MasColor[3] = 140;
      MasColor[4] = 200;
    }
    if (MemorNameMode == "One color") {
      drawtext(MemorNameOneColor, ST77XX_WHITE, 40, 50);
      drawtext("Brightness:" + (String)settings.BRIGHTNESS, ST77XX_WHITE, 30, 100);
      drawtext("______________", ST77XX_BLUE, 30, 70);
      drawtext("______________", ST77XX_YELLOW, 30, 155);
      POSMAX = 3;
      MasColor[1] = 50;
      MasColor[2] = 100;
      //      MasColor[3] = 140;
      MasColor[3] = 200;
    }
    if (MemorNameMode == "Off") {
      POSMAX = 1;
      MasColor[1] = 200;
      MasColor[2] = NULL;
    }

    drawtext("Back", ST77XX_WHITE, 30, 200);
    drawPointerMas(newPos, MasColor);
  }

  if (PassFlag) {
    PassFlag = 0;
    switch (MasColor[newPos]) {
      case 20:
        settings.IdMenu = 2;
        flag = true;
        drawPointer(">", ST77XX_BLACK, 0, 20);
        POSMAX = 2;
        encoder.setPosition(settings.IdColorMode);
        newPos = settings.IdColorMode;
        break;
      case 50:
        if (MemorNameMode == "Effects") {
          settings.IdMenu = 3;
          flag = true;
          drawPointer(">", ST77XX_BLACK, 0, 50);  //void drawPointer(char *text , uint16_t color,int x, int y)
          POSMAX = 39;
          encoder.setPosition(settings.IdColorEffects);
          //newPos = IdColorEffects;
        }
        if (MemorNameMode == "One color") {
          settings.IdMenu = 4;
          flag = true;
          drawPointer(">", ST77XX_BLACK, 0, 50);  //void drawPointer(char *text , uint16_t color,int x, int y)
          POSMAX = 137;
          encoder.setPosition(settings.IdOneColor);
          //newPos = IdOneColor;
        }
        break;
      case 100:
        settings.IdMenu = 5;
        flag = true;
        drawPointer(">", ST77XX_BLACK, 0, 100);  //void drawPointer(char *text , uint16_t color,int x, int y)
        POSMAX = 20;
        encoder.setPosition(settings.BRIGHTNESS / 5);
        //STEPS = 5;
        break;
      case 140:
        settings.IdMenu = 6;
        flag = true;
        drawPointer(">", ST77XX_BLACK, 0, 140);  //void drawPointer(char *text , uint16_t color,int x, int y)
        POSMAX = 20;
        encoder.setPosition(settings.speedColorEffect / 5);  //   /5
        break;
      case 200:
        //tft.fillScreen(ST77XX_BLACK);
        ClearColorMenu();
        encoder.setPosition(0);
        MasMenu[0] = 90;
        MasMenu[1] = 120;
        MasMenu[2] = 100;
        newPos = 0;
        settings.IdMenu = 0;
        flag = true;
        SaveSettings();
        drawPointer(">", ST77XX_WHITE, 70, 90);
        drawPointer(">", ST77XX_BLACK, 0, 200);
        break;
    }
  }
}

void MColorMode() {
  // OFF / OneColor / Effects
  //Setting MColorModeEffects
  POSMIN = 0;
  POSMAX = 2;
  //===============
  if (flag) {
    flag = false;
    drawPointer("<", ST77XX_WHITE, 295, 20);

    settings.IdColorMode = newPos;
    if (MemorNameMode != StrNameMode[settings.IdColorMode]) {
      drawtext(MemorNameMode, ST77XX_BLACK, 130, 20);
      drawtext(StrNameMode[settings.IdColorMode], ST77XX_WHITE, 130, 20);
      MemorNameMode = StrNameMode[settings.IdColorMode];

      if (MemorNameMode == "Effects") {
        drawtext(MemorNameOneColor, ST77XX_BLACK, 40, 50);
        drawtext(MemorNameEffect, ST77XX_WHITE, 40, 50);
        drawtext("Brightness:" + (String)settings.BRIGHTNESS, ST77XX_WHITE, 30, 100);
        drawtext("Speed work:" + (String)settings.speedColorEffect, ST77XX_WHITE, 30, 140);
        drawtext("______________", ST77XX_BLUE, 30, 70);
        drawtext("______________", ST77XX_YELLOW, 30, 155);
      }
      if (MemorNameMode == "One color") {
        drawtext(MemorNameEffect, ST77XX_BLACK, 40, 50);
        drawtext(MemorNameOneColor, ST77XX_WHITE, 40, 50);
        drawtext("Brightness:" + (String)settings.BRIGHTNESS, ST77XX_WHITE, 30, 100);
        drawtext("Speed work:" + (String)settings.speedColorEffect, ST77XX_BLACK, 30, 140);
        drawtext("______________", ST77XX_BLUE, 30, 70);
        drawtext("______________", ST77XX_YELLOW, 30, 155);
      }
      if (MemorNameMode == "Off") {
        drawtext(MemorNameOneColor, ST77XX_BLACK, 40, 50);
        drawtext(MemorNameEffect, ST77XX_BLACK, 40, 50);
        drawtext("______________", ST77XX_BLACK, 30, 70);
        drawtext("______________", ST77XX_BLACK, 30, 155);
        drawtext("Brightness:" + (String)settings.BRIGHTNESS, ST77XX_BLACK, 30, 100);
        //drawtext("Speed work:" + (String)speedColorEffect, ST77XX_BLACK, 30, 140);
      }
    }
    SaveSettings();
  }

  if (PassFlag) {
    encoder.setPosition(0);
    drawPointer("<", ST77XX_BLACK, 295, 20);
    drawPointer(">", ST77XX_WHITE, 0, 20);
    settings.IdMenu = 1;
    PassFlag = 0;
    flag = false;
    SaveSettings();
  }
}

//Функція відповідальна за виведення на дислей під меню "ColorModeEffects"
void MColorModeEffects() {
  //Setting MColorModeEffects
  POSMIN = 0;
  POSMAX = 39;
  //===============
  if (flag) {
    flag = false;
    drawPointer("<", ST77XX_WHITE, 295, 50);
    settings.IdColorEffects = newPos;
    if (MemorNameEffect != StrNameEffect[settings.IdColorEffects]) {
      drawtext(MemorNameEffect, ST77XX_BLACK, 40, 50);
      drawtext(StrNameEffect[settings.IdColorEffects], ST77XX_WHITE, 40, 50);
      MemorNameEffect = StrNameEffect[settings.IdColorEffects];
      SaveSettings();
    }
  }

  if (PassFlag) {
    encoder.setPosition(1);
    drawPointer("<", ST77XX_BLACK, 295, 50);
    drawPointer(">", ST77XX_WHITE, 0, 50);
    settings.IdMenu = 1;
    PassFlag = 0;
    flag = false;
    SaveSettings();
  }
}

//Функція відповідальна за виведення на дислей під меню "ColorModeOneColor"
void MColorModeOneColor() {
  //Setting MColorModeEffects
  POSMIN = 0;
  POSMAX = 137;
  //===============
  if (flag) {
    flag = false;
    drawPointer("<", ST77XX_WHITE, 295, 50);
    settings.IdOneColor = newPos;
    if (MemorNameOneColor != StrNameOneColor[settings.IdOneColor]) {
      drawtext(MemorNameOneColor, ST77XX_BLACK, 40, 50);
      drawtext(StrNameOneColor[settings.IdOneColor], ST77XX_WHITE, 40, 50);
      MemorNameOneColor = StrNameOneColor[settings.IdOneColor];
      SaveSettings();
    }
  }

  if (PassFlag) {
    encoder.setPosition(1);
    drawPointer("<", ST77XX_BLACK, 295, 50);
    drawPointer(">", ST77XX_WHITE, 0, 50);
    settings.IdMenu = 1;
    PassFlag = 0;
    flag = false;
    SaveSettings();
  }
}

void MColorBrightness() {
  //Setting MColorModeEffects
  POSMIN = 0;
  POSMAX = 20;
  //===============
  if (flag) {
    flag = false;
    drawPointer("<", ST77XX_WHITE, 295, 100);

    //    MemorBRIGHTNESS  //
    if (settings.BRIGHTNESS != newPos) {
      drawtext((String)settings.BRIGHTNESS, ST77XX_BLACK, 228, 100);
      settings.BRIGHTNESS = newPos;
      settings.BRIGHTNESS = settings.BRIGHTNESS * 5;  //STEPS 5
      drawtext((String)settings.BRIGHTNESS, ST77XX_WHITE, 228, 100);
      //MemorNameOneColor = StrNameOneColor[IdOneColor];
      MemorBRIGHTNESS = settings.BRIGHTNESS * 2.55;
      FastLED.setBrightness(MemorBRIGHTNESS);
      Serial.println(MemorBRIGHTNESS);
      SaveSettings();
    }
  }

  if (PassFlag) {
    encoder.setPosition(2);
    drawPointer("<", ST77XX_BLACK, 295, 100);
    drawPointer(">", ST77XX_WHITE, 0, 100);
    settings.IdMenu = 1;
    PassFlag = 0;
    //STEPS = 1;
    flag = false;
    SaveSettings();
  }
}

void SpeedColorEffect() {
  //Setting MColorModeEffects
  POSMIN = 0;
  POSMAX = 20;
  //===============
  if (flag) {
    flag = false;
    drawPointer("<", ST77XX_WHITE, 295, 140);

    if (settings.speedColorEffect != newPos) {
      drawtext((String)settings.speedColorEffect, ST77XX_BLACK, 228, 140);
      settings.speedColorEffect = newPos;
      settings.speedColorEffect = settings.speedColorEffect * 5;  //STEPS 5
      MemorSpeedColorEffect = (100 - settings.speedColorEffect);
      drawtext((String)settings.speedColorEffect, ST77XX_WHITE, 228, 140);
      Serial.println(settings.speedColorEffect);
      SaveSettings();
    }
  }

  if (PassFlag) {
    encoder.setPosition(3);
    drawPointer("<", ST77XX_BLACK, 295, 140);
    drawPointer(">", ST77XX_WHITE, 0, 140);
    settings.IdMenu = 1;
    PassFlag = 0;
    flag = false;
    SaveSettings();
  }
}

void Settings() {
  //Setting Settings
  POSMIN = 0;
  POSMAX = 4;
  //===============

  if (flag == true) {
    drawtext("DisplayBRG:" + (String)settings.CountDisplayBRG, ST77XX_WHITE, 30, 20);  // Яскравість дисплею
    drawtext("TSleepDisp:" + (String)TimeSleepDisplay[settings.CountTimeSleepDisplay], ST77XX_WHITE, 30, 55);
    //drawtext(TimeSleepDisplay[settings.CountTimeSleepDisplay], ST77XX_WHITE, 228, 60);
    drawtext("Factory reset", ST77XX_WHITE, 30, 90);
    drawtext("Author", ST77XX_WHITE, 30, 125);
    drawtext("_______________", ST77XX_WHITE, 30, 165);
    drawtext("Back", ST77XX_WHITE, 30, 200);
    drawPointerMas(newPos, MasSettings);
    flag = false;
  }

  if (PassFlag) {
    PassFlag = 0;
    switch (MasSettings[newPos]) {
      case 20:
        settings.IdMenu = 8;
        flag = true;
        drawPointer(">", ST77XX_BLACK, 0, 20);  //void drawPointer(char *text , uint16_t color,int x, int y)
        POSMAX = 10;
        encoder.setPosition(settings.CountDisplayBRG / 10);
        break;
      case 55:
        settings.IdMenu = 10;
        flag = true;
        drawPointer(">", ST77XX_BLACK, 0, 55);  //void drawPointer(char *text , uint16_t color,int x, int y)
        POSMAX = 6;
        encoder.setPosition(settings.CountTimeSleepDisplay);
        newPos = settings.CountTimeSleepDisplay;
        break;
      case 90:
        //Restart();
        ClearSettings();
        drawPointer(">", ST77XX_BLACK, 0, 90);
        settings.IdMenu = 11;
        flag = true;
        POSMAX = 0;
        encoder.setPosition(0);
        newPos = 0;
        break;
      case 125:
        ClearSettings();
        drawPointer(">", ST77XX_BLACK, 0, 125);
        settings.IdMenu = 9;
        flag = true;
        POSMAX = 0;
        break;
      case 200:
        ClearSettings();
        settings.IdMenu = 0;
        flag = true;
        newPos = 1;
        encoder.setPosition(1);
        drawPointer(">", ST77XX_BLACK, 0, 200);
        break;
    }
  }
}


void DisplayBRG() {
  //Setting DisplayBRG
  POSMIN = 1;
  POSMAX = 10;
  //===============
  if (flag) {
    flag = false;
    drawPointer("<", ST77XX_WHITE, 295, 20);

    if (settings.CountDisplayBRG != newPos) {
      drawtext((String)settings.CountDisplayBRG, ST77XX_BLACK, 228, 20);
      settings.CountDisplayBRG = newPos;
      settings.CountDisplayBRG = settings.CountDisplayBRG * 10;
      drawtext((String)settings.CountDisplayBRG, ST77XX_WHITE, 228, 20);
      MemorCountDisplayBRG = settings.CountDisplayBRG * 2.55;
      m = MemorCountDisplayBRG;
      analogWrite(LedDisplay, MemorCountDisplayBRG);
      Serial.println(MemorCountDisplayBRG);
      SaveSettings();
    }
  }

  if (PassFlag) {
    POSMIN = 0;
    encoder.setPosition(0);
    drawPointer("<", ST77XX_BLACK, 295, 20);
    drawPointer(">", ST77XX_WHITE, 0, 20);
    settings.IdMenu = 7;
    PassFlag = 0;
    flag = false;
    SaveSettings();
  }
}

void AutohorMenu() {
  //Setting AutohorMenu
  POSMIN = 0;
  POSMAX = 0;
  //===============
  if (flag) {
    flag = false;
    drawPointer("<", ST77XX_WHITE, 60, 200, 2);
    drawtext("Project name:", ST77XX_WHITE, 10, 20, 2);
    drawtext("Cooler ARGB lighting", ST77XX_WHITE, 10, 40, 2);
    drawtext("controller |-v 1.0|", ST77XX_WHITE, 10, 60, 2);
    drawtext("Author: Shchyryy Vitaliy", ST77XX_WHITE, 10, 80, 2);
    drawtext("GitHub https://github.com /Shchyryy", ST77XX_WHITE, 10, 120, 2);
    drawtext("Back", ST77XX_WHITE, 10, 200, 2);
  }
  if (PassFlag) {
    CleanAuthor();
    POSMAX = 4;          //якщо не працює переназначення курсора, потрібно зміннити PosMax до значення, яке містить меню, до якого повертаються
    newPos = 3;
    encoder.setPosition(3);
    drawPointer("<", ST77XX_BLACK, 60, 200, 2);
    settings.IdMenu = 7;
    PassFlag = 0;
    flag = true;
  }
}

void SleepDispMenu() {
  //Setting SleepDispMenu
  POSMIN = 0;
  POSMAX = 6;
  //===============
  if (flag) {
    flag = false;
    drawPointer("<", ST77XX_WHITE, 295, 55);

    if (settings.CountTimeSleepDisplay != newPos) {
      drawtext(TimeSleepDisplay[settings.CountTimeSleepDisplay], ST77XX_BLACK, 228, 55);
      settings.CountTimeSleepDisplay = newPos;
      drawtext(TimeSleepDisplay[settings.CountTimeSleepDisplay], ST77XX_WHITE, 228, 55);
      switch (settings.CountTimeSleepDisplay) {
        case 0:
          timeSleep = 0;  //Off
          break;
        case 1:
          timeSleep = 15;
          break;
        case 2:
          timeSleep = 30;
          break;
        case 3:
          timeSleep = 60;
          break;
        case 4:
          timeSleep = 120;
          break;
        case 5:
          timeSleep = 300;
          break;
        case 6:
          timeSleep = 600;
          break;
      }
      // Serial.println(timeSleep);
      // Serial.println(newPos);
      SaveSettings();
    }
  }
  if (PassFlag) {
    POSMIN = 0;
    newPos = 1;
    encoder.setPosition(1);
    drawPointer("<", ST77XX_BLACK, 295, 55);
    drawPointer(">", ST77XX_WHITE, 0, 55);
    settings.IdMenu = 7;
    PassFlag = 0;
    flag = true;
    SaveSettings();
  }
}

void FactoryResetMenu() {
  //Setting FactoryResetMenu
  POSMIN = 0;
  POSMAX = 1;
  //===============
  if (flag) {
    flag = false;
    if (newPos == 1) {
      drawPointer("<", ST77XX_BLACK, 220, 140, 2);
      drawPointer("<", ST77XX_WHITE, 133, 140, 2);
    } else {
      drawPointer("<", ST77XX_BLACK, 133, 140, 2);
      drawPointer("<", ST77XX_WHITE, 220, 140, 2);
    }
    drawtext("|   Reset the device   |", ST77XX_WHITE, 15, 70, 2);
    drawtext("| to factory settings? |", ST77XX_WHITE, 15, 100, 2);
    drawtext("Yes", ST77XX_GREEN, 90, 140, 2);
    drawtext("No", ST77XX_RED, 190, 140, 2);
  }
  if (PassFlag) {
    switch (newPos) {
      case 1:
        ClearFactoryResetMenu();
        settings.IdMenu = 0;
        settings.IdColorMode = 0;
        settings.IdColorEffects = 0;
        settings.IdOneColor = 0;
        settings.BRIGHTNESS = 80;
        settings.speedColorEffect = 80;
        settings.CountDisplayBRG = 100;
        settings.CountTimeSleepDisplay = 0;
        EEPROM.begin(Size_EEPROM);
        EEPROM.put(1, settings);
        EEPROM.end();
        ESP.restart();
        break;
      case 0:
        POSMIN = 0;
        POSMAX = 4;
        ClearFactoryResetMenu();
        newPos = 2;
        encoder.setPosition(2);
        drawPointer(">", ST77XX_WHITE, 0, 90);
        settings.IdMenu = 7;
        PassFlag = 0;
        flag = true;
        break;
    }
  }
}




//   if(newPos == 0){
//     drawtext("\\click to restart", ST77XX_BLACK, 120, 200, 2);
//   }
//   else if(newPos == 1) {
//     drawtext("\\click to", ST77XX_BLACK, 130, 195, 2);
//     drawtext(" \\Factory reset", ST77XX_BLACK, 130, 215, 2);
//     drawtext("\\click to restart", ST77XX_WHITE, 120, 200, 2);
//   }
//   else if(newPos == 2){
//     drawtext("\\click to restart", ST77XX_BLACK, 120, 200, 2);
//     drawtext("\\click to", ST77XX_WHITE, 130, 195, 2);
//     drawtext(" \\Factory reset", ST77XX_WHITE, 130, 215, 2);
//   }
//   else{
//     drawtext("\\click to", ST77XX_BLACK, 130, 195, 2);
//     drawtext(" \\Factory reset", ST77XX_BLACK, 130, 215, 2);
//   }
// }

void Restart() {
  ESP.restart();
}

void ClearMenu() {
  drawtext("|  Color   |", ST77XX_BLACK, 50, 90);
  drawtext("|  Setting |", ST77XX_BLACK, 50, 120);
}

void ClearSettings() {
  drawtext("DisplayBRG:" + (String)settings.CountDisplayBRG, ST77XX_BLACK, 30, 20);  // Яскравість дисплею
  //drawtext("Restart", ST77XX_BLACK, 30, 60);
  drawtext("TSleepDisp:" + (String)TimeSleepDisplay[settings.CountTimeSleepDisplay], ST77XX_BLACK, 30, 55);
  drawtext("Factory reset", ST77XX_BLACK, 30, 90);
  drawtext("Author", ST77XX_BLACK, 30, 125);
  drawtext("_______________", ST77XX_BLACK, 30, 165);
  drawtext("Back", ST77XX_BLACK, 30, 200);
  //drawPointerMas(newPos, MasSettings);
}

void CleanAuthor() {
  drawtext("Project name:", ST77XX_BLACK, 10, 20, 2);
  drawtext("Cooler ARGB lighting", ST77XX_BLACK, 10, 40, 2);
  drawtext("controller |-v 1.0|", ST77XX_BLACK, 10, 60, 2);
  drawtext("Author: Shchyryy Vitaliy", ST77XX_BLACK, 10, 80, 2);
  drawtext("GitHub https://github.com /Shchyryy", ST77XX_BLACK, 10, 120, 2);
  drawtext("Back", ST77XX_BLACK, 10, 200, 2);
}

void ClearColorMenu() {
  drawtext("Mode: ", ST77XX_BLACK, 30, 20);
  drawtext(MemorNameMode, ST77XX_BLACK, 130, 20);
  drawtext(MemorNameOneColor, ST77XX_BLACK, 40, 50);
  drawtext(MemorNameEffect, ST77XX_BLACK, 40, 50);
  drawtext("______________", ST77XX_BLACK, 30, 70);
  drawtext("______________", ST77XX_BLACK, 30, 155);
  drawtext("Brightness:" + (String)settings.BRIGHTNESS, ST77XX_BLACK, 30, 100);
  drawtext("Speed work:" + (String)settings.speedColorEffect, ST77XX_BLACK, 30, 140);
  drawtext("Back", ST77XX_BLACK, 30, 200);
}

void ClearFactoryResetMenu() {
  drawPointer("<", ST77XX_BLACK, 220, 140, 2);
  drawPointer("<", ST77XX_BLACK, 133, 140, 2);
  drawtext("|   Reset the device   |", ST77XX_BLACK, 15, 70, 2);
  drawtext("| to factory settings? |", ST77XX_BLACK, 15, 100, 2);
  drawtext("Yes", ST77XX_BLACK, 90, 140, 2);
  drawtext("No", ST77XX_BLACK, 190, 140, 2);
}
