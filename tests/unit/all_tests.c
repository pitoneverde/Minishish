#include "unity.h"
#include "minishell.h"

void setUp(void) { /* eseguito prima di ogni test */ }
void tearDown(void) { /* eseguito dopo ogni test  */ }

/* prototipi definiti nei file di test */
void test_sample_ast_building(void);

void test_tokenizer_basic(void);
void test_tokenizer_spaces(void);
void test_tokenize_empty_string(void);
void test_tokenize_only_spaces(void);
void test_tokenize_null_input(void);
void test_tokenize_quoted_escaped_string(void);
void test_tokenize_mixed_quotes_concat(void);
void test_tokenize_special_symbols(void);
void test_tokenize_attached_symbols(void);
void test_tokenize_unclosed_escaped_double_quote(void);
void test_tokenize_unclosed_double_quote_should_error(void);
void test_tokenize_pipeline_no_spaces(void);

int main(void)
{
    UNITY_BEGIN();

	/* Core AST library*/
	// RUN_TEST(test_sample_ast_building);
    /* Tokenizer */
    RUN_TEST(test_tokenizer_basic);
    RUN_TEST(test_tokenizer_spaces);
    RUN_TEST(test_tokenize_empty_string);
    RUN_TEST(test_tokenize_only_spaces);
    RUN_TEST(test_tokenize_null_input);
    RUN_TEST(test_tokenize_quoted_escaped_string);
    RUN_TEST(test_tokenize_mixed_quotes_concat);
    RUN_TEST(test_tokenize_special_symbols);
    RUN_TEST(test_tokenize_attached_symbols);
    RUN_TEST(test_tokenize_unclosed_escaped_double_quote);
    RUN_TEST(test_tokenize_unclosed_double_quote_should_error);
    RUN_TEST(test_tokenize_pipeline_no_spaces);

    /* Lexer */


    return UNITY_END();
}