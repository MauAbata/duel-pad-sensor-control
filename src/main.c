#include "mfrc522.h"
#include "twi.h"
#include "uart.h"
#include "ygo_card.h"
#include <avr/pgmspace.h>
#include <stdio.h>
#include <util/delay.h>

#define MFRC_ADDR 0b01010000
#define ERRCHK(expr)                                                                               \
    {                                                                                              \
        int err = expr;                                                                            \
        if (err != 0) {                                                                            \
            printf("%s = 0x%02x (0x%02x)\n", #expr, err, err << 2);                                \
            return err;                                                                            \
        }                                                                                          \
    }

int mfrc_write_twi(uint8_t reg, const uint8_t *data, size_t len) {
    ERRCHK(twi_start(MFRC_ADDR, WRITE));
    ERRCHK(twi_write(reg));
    for (size_t i = 0; i < len; i++) {
        ERRCHK(twi_write(data[i]));
    }
    ERRCHK(twi_stop());
    return 0;
}

int mfrc_read_twi(uint8_t reg, uint8_t *data, size_t len) {
    ERRCHK(twi_start(MFRC_ADDR, WRITE));
    ERRCHK(twi_write(reg));
    ERRCHK(twi_start(MFRC_ADDR, READ));
    for (size_t i = 0; i < len; i++) {
        ERRCHK(twi_read(&data[i], i == len - 1 ? NACK : ACK));
    }
    ERRCHK(twi_stop());
    return 0;
}

int mfrc_reset_gpio_write(uint8_t val) {
    if (val)
        PORTB |= (1 << PB3);
    else
        PORTB &= ~(1 << PB3);
    return 0;
}

int mfrc_delay_ms(uint32_t delay_ms) {
    while (delay_ms-- > 0)
        _delay_ms(1);
    return 0;
}

int main(void) {
    uart_init(9600);
    twi_init();

    if (1) {
        DDRB = (1 << PB2);
        PORTB &= ~(1 << PB3);
        _delay_ms(10);
        PORTB |= (1 << PB3);

        printf_P(PSTR("Scanning I2C Bus...\n"));

        for (uint8_t i = 0; i < 0x80; i++) {
            if (i % 0x10 == 0 && i != 0) printf("\n");

            int err = twi_start(i << 1, WRITE);

            if (err != 0) {
                printf("-- ");
            } else {
                printf("%02x ", i);
            }

            twi_stop();
            _delay_ms(10);
        }

        printf("\n");
    }

    printf_P(PSTR("Attempting to initialize MFRC522...\n"));

    mfrc522_config_t mfrc_config = {
        .twi_write = mfrc_write,
        .twi_read = mfrc_read,
        .reset_gpio_write = mfrc_reset_gpio_write,
        .delay_ms = mfrc_delay_ms,
    };

    mfrc522_err_t mfrc_err = mfrc522_init(&mfrc_config);

    if (mfrc_err != MFRC522_OK) {
        printf_P(PSTR("MFRC522 Init failed: 0x%02x\n"), mfrc_err);
        mfrc522_deinit();
        while (1)
            ;
    }

    ygo_card_t favorite_card;
    uint8_t favorite_card_bin[144] = {0x00};

    ygo_card_deserialize(&favorite_card, favorite_card_bin);
    ygo_card_print(&favorite_card);
}