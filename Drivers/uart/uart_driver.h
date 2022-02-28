
#ifndef __UART_DRIVER_H__
#define __UART_DRIVER_H__

#include "stm32f10x.h"

void uart_init(void);
void send_byte(uint8_t);
void send_data(uint8_t *dp);













#endif




