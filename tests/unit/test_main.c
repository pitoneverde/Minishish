#include "unity.h"
#include "minishell.h"

void setUp(void) { /* eseguito prima di ogni test */ }
void tearDown(void) { /* eseguito dopo ogni test  */ }

/* prototipi definiti nei file di test */
void test_tokenizer_basic(void);
void test_tokenizer_spaces(void);
void test_tokenize_empty_string(void);
void test_tokenize_null_input(void);
void test_tokenize_quoted_escaped_string(void);

int main(void)
{
    UNITY_BEGIN();

    /* Tokenizer */
    RUN_TEST(test_tokenizer_basic);
    RUN_TEST(test_tokenizer_spaces);
    RUN_TEST(test_tokenize_empty_string);
    RUN_TEST(test_tokenize_null_input);
    RUN_TEST(test_tokenize_quoted_escaped_string);

    return UNITY_END();
}