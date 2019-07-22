#ifndef CONFIG_H
#define CONFIG_H

#define USED_BUTTON 8 // max 32
#define BUTTON_PIN 16, 14, 12, 10, 8, 6, 4, 2, 0
#define LED_PIN 17, 15, 13, 11, 9, 7, 5, 3, 1

#define BUTTON_UP 0
#define BUTTON_DOWN 1
#define BUTTON_BACK 2
#define BUTTON_FORWARD 3
#define BUTTON_ENTER 4

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
#define GAME_REFLEX_SEQUENCE 10

enum
{
    NO_GAME_1,
    NO_GAME_2,
    __MAX_GAME
};
#define NUMBER_OF_GAMES __MAX_GAME

#define SCORE_PLAYER_LENGTH_NAME 9

#define EEPROM_START 0

#define DEBUG 1
#define SERIAL_BAUD_RATES 9600

#endif
