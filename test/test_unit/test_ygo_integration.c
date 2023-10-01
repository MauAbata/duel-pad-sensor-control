#include "ygo_card.h"
#include <string.h>
#include <unity.h>

#define NTAG213_MAX_MEM 144

void setUp(void) {
}
void tearDown(void) {
}

void test_card_struct_length(void) {
    ygo_card_t card;
    TEST_ASSERT_EQUAL(NTAG213_MAX_MEM, sizeof(card));
}

void test_card_serialization(void) {
    ygo_card_t card = {
        .id = 0xDEADBEEF,
        .type = 0x11,
        .frame = 0x22,
        .subtype = 0x33,
        .attribute = 0x44,
        .atk = 0x5566,
        .def = 0x7788,
        .rank = 0x99,
        .scale = 0xAA,
        .link_value = 0xBB,
        .link_markers = 0xCC,
        .name = "DEMONSTRATION CARD NAME",
    };

    uint8_t raw[NTAG213_MAX_MEM] = {0};
    ygo_card_serialize(raw, &card);

    uint8_t deadbeef[4] = {0xDE, 0xAD, 0xBE, 0xEF};
    TEST_ASSERT_EQUAL_HEX8_ARRAY(deadbeef, raw, 4);

    ygo_card_t clone;
    memset(&clone, 0, sizeof(clone));
    ygo_card_deserialize(&clone, raw);

    TEST_ASSERT_EQUAL_HEX32(card.id, clone.id);
    TEST_ASSERT_EQUAL_HEX8(card.type, clone.type);
    TEST_ASSERT_EQUAL_HEX8(card.frame, clone.frame);
    TEST_ASSERT_EQUAL_HEX8(card.subtype, clone.subtype);
    TEST_ASSERT_EQUAL_HEX8(card.attribute, clone.attribute);
    TEST_ASSERT_EQUAL_HEX16(card.atk, clone.atk);
    TEST_ASSERT_EQUAL_HEX16(card.def, clone.def);
    TEST_ASSERT_EQUAL_HEX8(card.rank, clone.rank);
    TEST_ASSERT_EQUAL_HEX8(card.scale, clone.scale);
    TEST_ASSERT_EQUAL_HEX8(card.link_value, clone.link_value);
    TEST_ASSERT_EQUAL_HEX8(card.link_markers, clone.link_markers);
    TEST_ASSERT_EQUAL_STRING_LEN(card.name, clone.name, YGO_CARD_NAME_MAX_LEN);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_card_struct_length);
    RUN_TEST(test_card_serialization);
    UNITY_END();
}