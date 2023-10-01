#include "ygo_card.h"

int main(void) {
    ygo_card_t favorite_card = {
        .name = "Dark Magician of Chaos",
        .type = YGO_CARD_TYPE_EFFECT_MONSTER,
        .frame = YGO_CARD_FRAME_EFFECT,
        .atk = 2800,
        .def = 2600,
        .rank = 8,
        .subtype = YGO_CARD_STYPE_MONSTER_SPELLCASTER,
        .attribute = YGO_CARD_ATTR_DARK,
    };

    favorite_card;
}