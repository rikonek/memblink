#ifndef CONFIG_H
#define CONFIG_H

#define USED_BUTTON 8 // max 32
#define BUTTON_PIN 16,14,12,10,8,6,4,2,0
#define LED_PIN 17,15,13,11,9,7,5,3,1

//#define SDA_PIN A4
//#define SCL_PIN A5

#define LCD_ADDR 0x27 // LCD I2C address
#define LCD_EN 2
#define LCD_RW 1
#define LCD_RS 0
#define LCD_D4 4
#define LCD_D5 5
#define LCD_D6 6
#define LCD_D7 7
#define LCD_BACKLIGHT_PIN 3
#define LCD_BACKLIGHT_POL POSITIVE

#define GAME_MEMORY_SEQUENCE 100 // max 255
#define NUMBER_OF_GAMES 1

#define EEPROM_G1P1_SCORE 0
#define EEPROM_G1P2_SCORE 21
//#define EEPROM_G2P1_SCORE 42
//#define EEPROM_G2P2_SCORE 63

#define DEBUG 1
#define SERIAL_BAUD_RATES 9600

#endif
