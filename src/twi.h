#ifndef __duel_pad_sensor_control__twi_h
#define __duel_pad_sensor_control__twi_h

#ifdef __cplusplus
extern "C" {
#endif

#include <avr/io.h>
#include <stdint.h>

enum twi_ack { ACK = 0x01, NACK = 0x00 };
typedef enum twi_ack twi_ack_t;

enum twi_read { READ = 0x01, WRITE = 0x00 };
typedef enum twi_read twi_read_t;

void twi_init(void);

int twi_start(uint8_t addr, twi_read_t rw);
int twi_repeat_start(uint8_t addr, twi_read_t rw);

int twi_write(uint8_t data);

int twi_read(uint8_t *dest, twi_ack_t ack);

int twi_stop(void);

#ifdef __cplusplus
}
#endif

#endif
