#include "mfrc522.h"
#include <string.h>

#ifndef MFRC522_USE_DYNAMIC_CONFIG
#define CONFIG(key) (sConfig.key)
static mfrc522_config_t sConfig;
#else
#define CONFIG(key) (sConfig->key)
static mfrc522_config_t *sConfig;
#endif

// Guard to ensure the necessary driver functions are installed
#define ASSERT_CONFIG                                                                              \
    if (CONFIG(twi_read) == NULL || CONFIG(twi_write) == NULL || CONFIG(delay_ms) == NULL ||       \
        CONFIG(reset_gpio_write) == NULL)                                                          \
        return MFRC522_ERR_BAD_CONFIG;

// Ensure a driver call succeeds, or return error code.
#define ASSERT_DRIVER_CALL(fn, ...)                                                                \
    {                                                                                              \
        uint8_t err = CONFIG(fn)(__VA_ARGS__);                                                     \
        if (err != 0) return (MFRC522_ERR_DRIVER_CALL_FAILED | (err & 0xF));                       \
    }

// Ensure a register write succeeds, or return an error code.
#define ASSERT_REGISTER_WRITE(reg, data, len) ASSERT_DRIVER_CALL(twi_write, reg, data, len)

// Ensure a register read succeeds, or return an error code.
#define ASSERT_REGISTER_READ(reg, data, len) ASSERT_DRIVER_CALL(twi_read, reg, data, len)

// Ensure a statement succeeds, or return its error code.
#define ASSERT(expr)                                                                               \
    {                                                                                              \
        int err = expr;                                                                            \
        if (err != 0) return err;                                                                  \
    }

mfrc522_err_t mfrc522_init(mfrc522_config_t *config) {
#ifdef MFRC522_USE_DYNAMIC_CONFIG
    sConfig = calloc(1, sizeof(mfrc522_config_t));
#else
    memset(&sConfig, 0, sizeof(mfrc522_config_t));
#endif

    // copy config struct element by element to allow for validation / error checking.
    CONFIG(twi_read) = config->twi_read;
    CONFIG(twi_write) = config->twi_write;

    CONFIG(reset_gpio_write) = config->reset_gpio_write;
    CONFIG(delay_ms) = config->delay_ms;

    // Perform chip initialization here.
    ASSERT_CONFIG

    // Perform Hard Reset
    ASSERT_DRIVER_CALL(reset_gpio_write, 0);
    ASSERT_DRIVER_CALL(delay_ms, 10);
    ASSERT_DRIVER_CALL(reset_gpio_write, 1);

    // Perform Soft Reset
    ASSERT(mfrc522_wait_command(MFRC522_CMD_SOFT_RESET));

    // Validate ID
    uint8_t id;
    ASSERT_REGISTER_READ(MFRC522_REG_VERSION, &id, 1);

    if (((id >> 4) & 0xF) != 0x9) {
        return MFRC522_ERR_INVALID_DEVICE_ID;
    }

    return MFRC522_OK;
}
#include <stdio.h>
mfrc522_err_t mfrc522_wait_command(uint8_t command) {
    uint8_t cmd_reg;
    uint32_t timeout;

    ASSERT_REGISTER_READ(MFRC522_REG_COMMAND, &cmd_reg, 1);

    // todo: convert to named macros
    cmd_reg &= ~(0xF << 0);
    cmd_reg |= MFRC522_CMD_SOFT_RESET;

    ASSERT_REGISTER_WRITE(MFRC522_REG_COMMAND, &cmd_reg, 1);
    ASSERT_DRIVER_CALL(delay_ms, 1);

    timeout = 1000;
    while (timeout > 0) {
        ASSERT_REGISTER_READ(MFRC522_REG_COMMAND, &cmd_reg, 1);

        printf("d:%04ld r:%02X\n", timeout, cmd_reg);

        // todo: convert to named macro
        if (cmd_reg & (1 << 4) == 0) {
            break;
        }

        timeout--;

        if (timeout == 0) {
            return MFRC522_ERR_COMMAND_TIMEOUT;
        }

        ASSERT_DRIVER_CALL(delay_ms, 1);
    }

    return MFRC522_OK;
}

void mfrc522_deinit(void) {
    // Perform chip de-initialization here.

#ifdef MFRC522_USE_DYNAMIC_CONFIG
    free(sConfig);
#else
    memset(&sConfig, 0, sizeof(mfrc522_config_t));
#endif
}