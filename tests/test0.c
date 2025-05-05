#include "unity.h"

void setUp(void)   { /* eseguito prima di ogni test */ }
void tearDown(void){ /* eseguito dopo ogni test  */ }

void test_one_plus_one(void) {
    TEST_ASSERT_EQUAL_INT(2, 1 + 1);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_one_plus_one);
    return UNITY_END();
}