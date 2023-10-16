#include "twi.h"
#include <util/twi.h>

#define SCL_CLOCK 100000UL

#define TWI_ASSERT(status)                                                                         \
    if (TW_STATUS != (status)) return (0x80 | (TW_STATUS >> 2));

#define wait_ready()                                                                               \
    while ((TWCR & (1 << TWINT)) == 0)                                                             \
        ;

void twi_init(void) {
    TWSR = 0x00;
    TWBR = ((F_CPU / SCL_CLOCK) - 16) / 2;
    TWCR = (1 << TWEN);
}

int twi_start(uint8_t addr, twi_read_t read) {
    if (TW_STATUS == 0x00) {
        // Clear out a bus error
        TWCR = (1 << TWINT) | (1 << TWSTO);
    }

    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    wait_ready();
    TWI_ASSERT(TW_START);

    TWDR = (addr & 0xFE) | (read & 0x1);
    TWCR = (1 << TWINT) | (1 << TWEN);
    wait_ready();
    TWI_ASSERT(TW_MT_SLA_ACK);

    return 0;
}

int twi_repeat_start(uint8_t addr, twi_read_t read) {
    if (TW_STATUS == 0x00) {
        // Clear out a bus error
        TWCR = (1 << TWINT) | (1 << TWSTO);
    }

    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    wait_ready();
    TWI_ASSERT(TW_REP_START);

    TWDR = (addr & 0xFE) | (read & 0x1);
    TWCR = (1 << TWINT) | (1 << TWEN);
    wait_ready();
    TWI_ASSERT(TW_MT_SLA_ACK);

    return 0;
}

int twi_write(uint8_t data) {
    TWDR = data;
    TWCR = (1 << TWINT) | (1 << TWEN);
    wait_ready();
    TWI_ASSERT(TW_MT_DATA_ACK);
    return 0;
}

int twi_read(uint8_t *dest, twi_ack_t ack) {
    TWCR = (1 << TWINT) | (1 << TWEN) | (ack << TWEA);
    wait_ready();
    TWI_ASSERT(ack == ACK ? TW_MR_DATA_ACK : TW_MR_DATA_NACK);
    return 0;
}

int twi_stop(void) {
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
    // while ((TWCR & (1 << TWSTO)) == 1);
    return 0;
}