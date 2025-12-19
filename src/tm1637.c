#include "tm1637.h"
#include "tm1637_interface.h"

#define TM1637_MODE         0x40 // Display mode, Automatic address incrementing, Normal mode

#define TM1637_ADR1         0xC0
#define TM1637_ADR2         0xC1
#define TM1637_ADR3         0xC2
#define TM1637_ADR4         0xC3

#define TM1637_CONTROL_ON   0x88
#define TM1637_CONTROL_OFF  0x80

const uint8_t digitHEX[] = {0x3f, 0x06, 0x5b, 0x4f,
    0x66, 0x6d, 0x7d, 0x07,
    0x7f, 0x6f, 0x00, 0x40
}; //0~9, ,-

void tm1637_init (const tm1637_t* unit) {
    assert_param(unit != NULL);
    assert_param(unit->GPIO_CLK != NULL);
    assert_param(unit->GPIO_DIO != NULL);
    assert_param(IS_GPIO_PIN(unit->PIN_DIO));
    assert_param(IS_GPIO_PIN(unit->PIN_CLK));

    tm1637_start(unit);
    tm1637_writeByte(unit, TM1637_MODE);
    tm1637_brightness (unit, 8);
    tm1637_stop(unit);

    tm1637_clear(unit);

}

void tm1637_sendByte  (const tm1637_t* unit, const tm1637_address_t adr, const uint8_t data) {
    const uint8_t address = TM1637_ADR1 | (adr & 0x03);
    tm1637_start(unit);
    tm1637_writeByte(unit, address);
    tm1637_writeByte(unit, data);
    tm1637_stop(unit);
}

void tm1637_sendArray (const tm1637_t* unit, uint8_t data[4]) {
    assert_param(unit != NULL);

    tm1637_start(unit);
    tm1637_writeByte(unit, TM1637_ADR1);
    for (uint8_t i=0; i < 4; i++) {
        tm1637_writeByte(unit, data[i]);
    }
    tm1637_stop(unit);
}

void tm1637_brightness (const tm1637_t *unit, const uint8_t level) {
    const uint8_t data = (level > 0) ? TM1637_CONTROL_ON | (0b00000111 & (level - 1)) : TM1637_CONTROL_OFF;
    tm1637_start(unit);
    tm1637_writeByte(unit, data);
    tm1637_stop(unit);
}

void tm1637_clear (const tm1637_t* unit) {
    uint8_t send_buff[4] = {0, 0, 0, 0};
    tm1637_start(unit);
    tm1637_sendArray(unit, send_buff);
    tm1637_stop(unit);
}

void tm1637_display (const tm1637_t* unit, const tm1637_simbol_t data[4]) {
    uint8_t send_buff [4];
    for (uint8_t i = 0; i < 4; i++) {
        if (data[i] > 11) return;
        send_buff [i] = digitHEX[(uint8_t)data[i]];
    }

    tm1637_sendArray(unit, send_buff);
}

void tm1637_displayInt (const tm1637_t* unit, int16_t data, const uint8_t isFill) {
    if (data > 9999 || data < -999) return;;

    uint8_t send_buff [4];
    const uint8_t minus_flag = (data >= 0) ? 0 : 1;
    if (minus_flag) data *= -1;

    for (uint8_t i = 3; i > 0; i--) {
        send_buff[i] = (data || i == 3 || isFill) ? digitHEX[data % 10] : digitHEX[10];
        data /= 10;
    }

    send_buff[0] = (minus_flag) ? digitHEX[11] :
                    (data || isFill) ? digitHEX[data] : digitHEX[10];
    tm1637_sendArray(unit, send_buff);
}

void tm1637_displayClock (const tm1637_t* unit, const uint8_t hours, const uint8_t minutes) {
    if (hours > 99 || minutes > 99) return;

    static uint32_t timer = 0; // TODO: bad use static value for many displays, but good for one.
    static uint8_t isPoint = 0;

    if (HAL_GetTick() - timer > 1000) {
        timer = HAL_GetTick();
        isPoint = !isPoint;
    }
    uint8_t send_buff [4] = {hours / 10, hours % 10, minutes / 10, minutes % 10};
    for (int i = 0; i < 4; i++) send_buff[i] = digitHEX[send_buff[i]];

    if (isPoint) send_buff[1] |= 0b10000000;

    tm1637_sendArray(unit, send_buff);
}


