#ifndef __mfrc522_reg_h
#define __mfrc522_reg_h

#ifdef __cplusplus
extern "C" {
#endif

// Starts and stops command execution.
#define MFRC522_REG_COMMAND 0x01
// Enable and disable interrupt request control bits
#define MFRC522_REG_COM_I_EN 0x02
// Enable and disable interrupt request control bits
#define MFRC522_REG_DIV_I_EN 0x03
// Interrupt request bits
#define MFRC522_REG_COM_IRQ 0x04
// Interrupt request bits
#define MFRC522_REG_DIV_IRQ 0x05
// Error bits showing the error status of the last command executed
#define MFRC522_REG_ERROR 0x06
// Communication status bits
#define MFRC522_REG_STATUS_1 0x07
// Receiver and transmitter status bits
#define MFRC522_REG_STATUS_2 0x08
// Input and output of 64 byte FIFO buffer
#define MFRC522_REG_FIFO_DATA 0x09
// Number of bytes stored in the FIFO buffer
#define MFRC522_REG_FIFO_LEVEL 0x0A
// Level for FIFO underflow and overflow warning
#define MFRC522_REG_WATER_LEVEL 0x0B
// Miscellaneous control registers
#define MFRC522_REG_CONTROL 0x0C
// Adjustments for bit-oriented frames
#define MFRC522_REG_BIT_FRAMING 0x0D
// Bit position of the first bit-collision detected on the RF interface
#define MFRC522_REG_COLL 0x0E

// Defines general modes for transmitting and receiving
#define MFRC522_REG_MODE 0x11
// Defines transmission data rate and framing
#define MFRC522_REG_TX_MODE 0x12
// Defines reception data rate and framing
#define MFRC522_REG_RX_MODE 0x13
// Controls the logical behavior of the antenna driver pins TX1 and TX2
#define MFRC522_REG_TX_CONTROL 0x14
// Controls the setting of the transmission modulation
#define MFRC522_REG_TX_ASK 0x15
// Selects the internal sources for the antenna driver
#define MFRC522_REG_TX_SEL 0x16
// Selects internal receiver settings
#define MFRC522_REG_RX_SEL 0x17
// Selects thresholds for the bit decoder
#define MFRC522_REG_RX_THRESHOLD 0x18
// Defines demodulator settings
#define MFRC522_REG_DEMOD 0x19
// Controls some MIFARE communication transmit parameters
#define MFRC522_REG_MF_TX 0x1C
// Controls some MIFARE communication receive parameters
#define MFRC522_REG_MF_RX 0x1D
// Selects the speed of the serial UART interface
#define MFRC522_REG_SERIAL_SPEED 0x1F

// Shows the MSB values of the CRC calculation
#define MFRC522_REG_CRC_RESULT_H 0x21
// Shows the LSB values of the CRC calculation
#define MFRC522_REG_CRC_RESULT_L 0x22
// Controls the ModWidth setting
#define MFRC522_REG_MOD_WIDTH 0x24
// Configures the receiver gain
#define MFRC522_REG_RF_CFG 0x26
// Selects the conductance of the antenna driver pins TX1 and TX2 for modulation
#define MFRC522_REG_GS_N 0x27
// Defines the conductance of the p-driver output during periods of no modulation
#define MFRC522_REG_CW_GS_P 0x28
// Defines the conductance of the p-driver output during periods of modulation
#define MFRC522_REG_MOD_GS_P 0x29
// Defines settings for the internal timer
#define MFRC522_REG_T_MODE 0x2A
// Defines settings for the internal timer
#define MFRC522_REG_T_PRESCALER 0x2B
// Defines the 16-bit timer reload value (High Byte)
#define MFRC522_REG_T_RELOAD_H 0x2C
// Defines the 16-bit timer reload value (Low Byte)
#define MFRC522_REG_T_RELOAD_L 0x2D
// Shows the 16-bit timer value (High Byte)
#define MFRC522_REG_T_COUNTER_VAL_H 0x2E
// Shows the 16-bit timer value (Low Byte)
#define MFRC522_REG_T_COUNTER_VAL_L 0x2F

// General test signal configuration
#define MFRC522_REG_TEST_SEL_1 0x31
// General test signal configuration and PRBS control
#define MFRC522_REG_TEST_SEL_2 0x32
// Enables pin output driver on pins D1 to D7
#define MFRC522_REG_TEST_PIN_EN 0x33
// Defines the values for D1 to D7 when it is used as an I/O bus
#define MFRC522_REG_TEST_PIN_VALUE 0x34
// Shows the status of the internal test bus
#define MFRC522_REG_TEST_BUS 0x35
// Controls the digital self test
#define MFRC522_REG_AUTO_TEST 0x36
// Shows the software version
#define MFRC522_REG_VERSION 0x37
// Controls the pins AUX1 and AUX2
#define MFRC522_REG_ANALOG_TEST 0x38
// Defines the test value for TestDAC1
#define MFRC522_REG_TEST_DAC_1 0x39
// Defines the test value for TestDAC2
#define MFRC522_REG_TEST_DAC_2 0x3A
// Shows the value of ADC I and Q channels
#define MFRC522_REG_TEST_ADC 0x3B

#ifdef __cplusplus
}
#endif

#endif
