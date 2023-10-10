#ifndef __duel_pad_sensor_control__uart_h
#define __duel_pad_sensor_control__uart_h

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

void uart_init(uint32_t baud);
void uart_set_baud(uint32_t baud);

#ifdef __cplusplus
}
#endif

#endif
