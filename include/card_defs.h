#ifndef __card_defs_h
#define __card_defs_h

#include "ygo_card.h"
#include <stdint.h>


//= Card Orientation Defs

/**
 * Card orientation on the play mat, as indicated by the top of the card facing this cardinal
 * direction. The order is such that bit position 2 can be tested to determine Attack and Defense
 * positions (see `is_defense_position`).
 *
 * This data uses a bitmask of 0b00000011
 */
enum card_orientation {
    CARD_ORIENT_NORTH = 0b00,
    CARD_ORIENT_SOUTH = 0b01,
    CARD_ORIENT_EAST = 0b10,
    CARD_ORIENT_WEST = 0b11,
};

#define CARD_ORIENTATION_BITS 0b00000011
typedef enum card_orientation card_orientation_t;

/**
 * Checks a card orientation from a card data field, returning 1 if defense position, 0 otherwise.
 */
#define is_defense_position(orient) ((orient >> 1) & 0b1)

//= Card Facing Defs

/**
 * Bit indicating whether the card is face up or face down. True value is face up. See `is_face_up`.
 *
 * This data uses a bitmask of 0b00000100
 */
enum card_facing {
    CARD_FACE_DOWN = 0b000,
    CARD_FACE_UP = 0b100,
};

#define CARD_FACING_BITS 0b00000100
typedef enum card_facing card_facing_t;

/**
 * Checks if the card data represents a face-up card. 1 is face up, 0 otherwise.
 */
#define is_face_up(facing) ((facing >> 2) & 0b1)

//= Card Read Status Defs

/**
 * Flags indicating the current state of the card read. Access as bitwise OR operations.
 *
 * This data uses a bitmask of 0b00111000
 */
enum card_read_state {
    CARD_READ_PRESENT = 0b001000,
    CARD_READ_FACING_ERR = 0b010000,
    CARD_READ_DATA_ERR = 0b100000,
};

#define CARD_READ_STATE_BITS 0b00111000
typedef enum card_read_state card_read_state_err;

/**
 * Checks a card state field for the card present bit.
 */
#define is_card_present(data) ((data >> 4) & 0b1)

/**
 * Checks a card state field for the absence of any error bits.
 */
#define is_card_read_valid(data) (!((data >> 5) & 0b11))

//= Complete card data structs:

struct card_read {
    uint8_t flags;
    card_data_t data;
};

typedef struct card_read card_read_t;

#endif