#ifndef DANGEL_TM1637_INTERFACE_H
#define DANGEL_TM1637_INTERFACE_H

#include "tm1637.h"

void tm1637_delay (uint8_t);
void tm1637_start(const tm1637_t *);
void tm1637_stop(const tm1637_t *);
void tm1637_waitAck (const tm1637_t *);
void tm1637_writeByte (const tm1637_t *, uint8_t);

#endif //DANGEL_TM1637_INTERFACE_H