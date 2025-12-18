//
// Created by dangel on 09.11.2025.
//

#include "tm1637_interface.h"

#define CLK_HIGH() unit->GPIO_CLK->BSRR = unit->PIN_CLK;
#define CLK_LOW()  unit->GPIO_CLK->BSRR = unit->PIN_CLK << 16;
#define DIO_HIGH() unit->GPIO_DIO->BSRR = unit->PIN_DIO;
#define DIO_LOW()  unit->GPIO_DIO->BSRR = unit->PIN_DIO << 16;


inline void tm1637_delay (uint8_t time) {
    for (int i=0; i < time; i++){
        for (int j=0; j<3; j++){
            __NOP();
        }
    }
}

void tm1637_writeByte (const tm1637_t *unit, uint8_t data) {
    assert_param(unit != NULL);

    for (uint8_t i = 0; i < 8; i++) {
        CLK_LOW();
        unit->GPIO_DIO->BSRR = data & 0x01 ? unit->PIN_DIO : unit->PIN_DIO << 16;
        tm1637_delay(3);
        CLK_HIGH();
        tm1637_delay(3);
        data = data >> 1;
    }
    tm1637_waitAck(unit);
}

void tm1637_start(const tm1637_t *unit) {
    assert_param(unit != NULL);
    CLK_HIGH();
    DIO_HIGH();
    tm1637_delay(2);
    DIO_LOW();
}

void tm1637_waitAck (const tm1637_t *unit) {
    CLK_LOW();
    tm1637_delay(5);
    //	while (dio);  // Check the state of the Data pin
    CLK_HIGH();
    tm1637_delay(2);
    CLK_LOW();
}

void tm1637_stop(const tm1637_t *unit) {
    assert_param(unit != NULL);
    CLK_LOW();
    tm1637_delay(2);
    DIO_LOW();
    tm1637_delay(2);
    CLK_HIGH();
    tm1637_delay(2);
    DIO_HIGH();
}