#include "unity.h"
#include "minishell.h"

void setUp(void)   { /* eseguito prima di ogni test */ }
void tearDown(void){ /* eseguito dopo ogni test  */ }

// Un test di esempio: verifica che somma(2,2) == 4
void test_sum(void) {
    TEST_ASSERT_EQUAL_INT(4, sum(2, 2));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_sum);
    return UNITY_END();
}