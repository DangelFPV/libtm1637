#ifndef DANGEL_TM1637_H
#define DANGEL_TM1637_H

#include "stm32f1xx.h"

typedef struct tm1637_t {
    GPIO_TypeDef*   GPIO_DIO;
    uint16_t        PIN_DIO;
    GPIO_TypeDef*   GPIO_CLK;
    uint16_t        PIN_CLK;
} tm1637_t;

typedef enum tm1637_address_t {
    DS1 = 0,
    DS2 = 1,
    DS3 = 2,
    DS4 = 3
} tm1637_address_t;

typedef enum tm1637_simbol_t {
    _0 = 0,
    _1 = 1,
    _2 = 2,
    _3 = 3,
    _4 = 4,
    _5 = 5,
    _6 = 6,
    _7 = 7,
    _8 = 8,
    _9 = 9,
    space = 10,
    minus = 11
} tm1637_simbol_t;

void tm1637_init       (const tm1637_t* unit);
void tm1637_brightness (const tm1637_t* unit, uint8_t level); // 0-8

void tm1637_sendByte   (const tm1637_t* unit, tm1637_address_t adr, uint8_t data);
void tm1637_sendArray  (const tm1637_t* unit, uint8_t data[4]);

void tm1637_clear      (const tm1637_t* unit);
void tm1637_display    (const tm1637_t* unit, const tm1637_simbol_t data[4]);
void tm1637_displayInt (const tm1637_t* unit, int16_t data, uint8_t isFill);
void tm1637_displayClock (const tm1637_t* unit, uint8_t hours, uint8_t minutes);

#endif //DANGEL_TM1637_H