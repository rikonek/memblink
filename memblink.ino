#include "config.h"
#include "lang_pl.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>

const unsigned int array_button[]={ BUTTON_PIN };
const unsigned int array_led[]={ LED_PIN };

LiquidCrystal_I2C lcd(LCD_ADDR, LCD_EN, LCD_RW, LCD_RS, LCD_D4, LCD_D5, LCD_D6, LCD_D7, LCD_BACKLIGHT_PIN, LCD_BACKLIGHT_POL);

typedef struct theBest
{
  uint8_t score=0;
  unsigned long time=0;
  char player[SCORE_PLAYER_LENGTH_NAME]={""};
} theBest;

typedef struct theScore
{
  theBest game[NUMBER_OF_GAMES];
} theScore;

void setup() {
  #if DEBUG
    Serial.begin(SERIAL_BAUD_RATES);
    Serial.println("Memblink. Please wait...");
  #endif

  lcd.begin(20,4); // LCD 20 chars 4 lines
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(LANG_DEVICE_NAME_PADDING,0);
  lcd.print(LANG_DEVICE_NAME);
  lcd.setCursor(LANG_PLEASE_WAIT_PADDING,2);
  lcd.print(LANG_PLEASE_WAIT);

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
  for(uint8_t i=0; i<NUMBER_OF_GAMES; i++)
  {
    ledOn(i);
  }

  #if DEBUG
    Serial.println("Choose a game.");
  #endif

  lcd.clear();
  lcd.setCursor(LANG_DEVICE_NAME_PADDING,0);
  lcd.print(LANG_DEVICE_NAME);
  lcd.setCursor(LANG_CHOOSE_GAME_PADDING,2);
  lcd.print(LANG_CHOOSE_GAME);

  #ifdef LANG_GAME1_NAME
    lcd.setCursor(0,3);
    lcd.print("1. ");
    lcd.print(LANG_GAME1_NAME);
  #endif

  while(game==-1 || game>=NUMBER_OF_GAMES)
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
