#ifndef __mfrc522_cmd_h
#define __mfrc522_cmd_h

#ifdef __cplusplus
extern "C" {
#endif

// No action, cancels the current command execution
#define MFRC522_CMD_IDLE 0x0
// Stores 25 bytes into the internal buffer
#define MFRC522_CMD_MEM 0x1
// Generates a 10-byte random ID number
#define MFRC522_CMD_RANDOM_ID 0x2
// Activates the CRC coprocessor or performs a self test
#define MFRC522_CMD_CALC_CRC 0x3
// Transmits data from the FIFO buffer
#define MFRC522_CMD_TRANSMIT 0x4
// No command change -- For modifying CommandReg without affecting the command
#define MFRC522_CMD_NO_CMD_CHANGE 0x7
// Activates the receiver circuits
#define MFRC522_CMD_RECEIVE 0x8
// Transmits data from FIFO buffer to antenna and automatically activates the receiver after
// transmission
#define MFRC522_CMD_TRANSCEIVE 0xC
// Performs the MIFARE standard authentication as a reader
#define MFRC522_CMD_MF_AUTH 0xE
// Resets the MFRC522
#define MFRC522_CMD_SOFT_RESET 0xF

#ifdef __cplusplus
}
#endif

#endif
