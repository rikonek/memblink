#include "config.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>

const unsigned int array_button[]={ BUTTON_PIN };
const unsigned int array_led[]={ LED_PIN };

void setup() {
  #if DEBUG
    Serial.begin(SERIAL_BAUD_RATES);
    Serial.println("Memblink. Please wait...");
  #endif

  for(uint8_t i=0; i<USED_BUTTON; i++)
  {
    pinMode(array_led[i], OUTPUT);
    ledOn(i);
    delay(60);
    ledOff(i);
  }

  for(uint8_t i=0; i<USED_BUTTON; i++)
  {
    pinMode(array_button[i], INPUT_PULLUP);
  }
}

void loop() {
  int8_t game=-1;
//  char player[20]="Test";

  allLedOff();
  ledOn(0); // Game 1 (memory) - player 1
  ledOn(1); // Game 1 (memory) - player 2
  ledOn(2); // Game 2 (reflex) - player 1
  ledOn(3); // Game 2 (reflex) - player 2

  Serial.println("Ready. Choose game.");
  while(game==-1 || game>3)
  {
    game=readButton();
  }

  ledCountDown();

  switch(game)
  {
    case 0:
      runG1P1();
      break;
  }
// Jeżeli wygrałeś to
// Serial.println("Podaj swoje imie...");
}
