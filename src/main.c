#include "uart.h"
#include "ygo_card.h"
#include <stdio.h>

int main(void) {
    uart_init(9600);

    ygo_card_t favorite_card = {
        .name = "Dark Magician of Chaos",
        .type = YGO_CARD_TYPE_MONSTER,
        .flags = YGO_MONSTER_FLAG_EFFECT,
        .atk = 2800,
        .def = 2600,
        .monster_type = YGO_MONSTER_TYPE_SPELLCASTER,
        .attribute = YGO_ATTRIBUTE_DARK,
    };

    printf("My favorite monster card is: %s, a %x type with %d ATK and %d DEF.\n",
           favorite_card.name,
           favorite_card.type,
           favorite_card.atk,
           favorite_card.def);

    ygo_card_print(&favorite_card);

    printf("The above.\n");
}