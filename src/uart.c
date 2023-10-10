#include "uart.h"
#include <avr/common.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

static int uart_putchar(char c, FILE *stream);
static FILE uart_stdout = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);

void uart_init(uint32_t baud) {
    UCSR0A = 0x00;
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
    UCSR0C = (1 << UMSEL01) | (1 << UCSZ01) | (1 << UCSZ00);

    uart_set_baud(baud);

    stdout = &uart_stdout;
    stderr = &uart_stdout;
}

void uart_set_baud(uint32_t baud) {
    unsigned long baud_reg = (F_CPU / 16 / baud) - 1;
    uint16_t reg = baud_reg & 0xFFFF;

    // TODO: Check baud rate range.
    UBRR0H = reg >> 8;
    UBRR0L = reg & 0xFF;
}

static int uart_putchar(char c, FILE *stream) {
    while (!(UCSR0A & (1 << UDRE0)))
        ;
    UDR0 = c;
    return 0;
}