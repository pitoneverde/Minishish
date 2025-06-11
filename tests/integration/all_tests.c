#include "unity.h"

#define main real_main
#include "../../src/main.c"
#undef main

/* prototipi definiti nei file di test */
void test_argc_troppi(void);
void test_prompt_ctrl_d_subito(void);
void test_prompt_empty_then_eof(void);

int main(void)
{
    UNITY_BEGIN();

    /* gruppo argc */
    RUN_TEST(test_argc_troppi);

    /* gruppo prompt */
    RUN_TEST(test_prompt_ctrl_d_subito);
    RUN_TEST(test_prompt_empty_then_eof);

    return UNITY_END();
}
