#include "twi.h"
#include <util/twi.h>

#define wait_ready()                                                                               \
    {                                                                                              \
        while ((TWCR & (1 << TWINT)) == 0)                                                         \
            ;                                                                                      \
    }

#define twi_status (TWSR & TW_STATUS_MASK)
#define twi_assert(status)                                                                         \
    if (twi_status != status) return twi_status;

void twi_init(void) {
    TWSR = 0x00;
    TWBR = 0x0C;
    TWCR = (1 << TWEN);
}

int twi_start(uint8_t addr, twi_read_t read) {
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    wait_ready();
    twi_assert(TW_START);

    twi_write((addr & 0xFE) | (read & 0x1));
    if (twi_status != TW_START || twi_status != TW_REP_START) return twi_status;
    return 0;
}

int twi_write(uint8_t data) {
    TWDR = data;
    TWCR = (1 << TWINT) | (1 << TWEN);
    wait_ready();
    twi_assert(TW_MT_DATA_ACK);
    return 0;
}

int twi_read(uint8_t *dest, twi_ack_t ack) {
    TWCR = (1 << TWINT) | (1 << TWEN) | (ack << TWEA);
    wait_ready();
    twi_assert(ack == ACK ? TW_MR_DATA_ACK : TW_MR_DATA_NACK);
    return 0;
}

int twi_stop(void) {
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
    return 0;
}