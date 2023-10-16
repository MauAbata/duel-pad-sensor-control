#ifndef __mfrc522_h
#define __mfrc522_h

#ifdef __cplusplus
extern "C" {
#endif

#include "mfrc522_cmd.h"
#include "mfrc522_reg.h"
#include <stddef.h>
#include <stdint.h>

typedef int (*mfrc522_data_write_fn_t)(uint8_t addr, const uint8_t *data, size_t len);
typedef int (*mfrc522_data_read_fn_t)(uint8_t addr, uint8_t *data, size_t len);
typedef int (*mfrc522_gpio_write_fn_t)(uint8_t value);
typedef int (*mfrc522_delay_ms_fn_t)(uint32_t delay_ms);

struct mfrc522_config {
    mfrc522_data_write_fn_t write;
    mfrc522_data_read_fn_t read;

    // System Specific
    mfrc522_gpio_write_fn_t reset_gpio_write;
    mfrc522_delay_ms_fn_t delay_ms;
};

typedef struct mfrc522_config mfrc522_config_t;

enum mfrc522_err {
    MFRC522_OK,
    MFRC522_ERR_BAD_CONFIG,
    MFRC522_ERR_COMMAND_TIMEOUT,
    MFRC522_ERR_INVALID_DEVICE_ID,
    MFRC522_ERR_DRIVER_CALL_FAILED = 0x10,
};

typedef enum mfrc522_err mfrc522_err_t;

mfrc522_err_t mfrc522_init(mfrc522_config_t *config);
void mfrc522_deinit(void);

mfrc522_err_t mfrc522_wait_command(uint8_t command);

#ifdef __cplusplus
}
#endif

#endif
