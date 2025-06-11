#include "unity.h"
#include "minishell.h"

// Suddividi stringa semplice
void test_tokenizer_basic(void)
{
    const char *input = "echo ciao mondo";
    t_list *tokens = tokenize(input);

    // Verifica che la lista non sia NULL
    TEST_ASSERT_NOT_NULL(tokens);
    
    // Primo token
    TEST_ASSERT_NOT_NULL(tokens->content);
    TEST_ASSERT_EQUAL_STRING("echo", (char *)tokens->content);
    tokens = tokens->next;

    // Secondo token
    TEST_ASSERT_NOT_NULL(tokens);
    TEST_ASSERT_EQUAL_STRING("ciao", (char *)tokens->content);
    tokens = tokens->next;

    // Terzo token
    TEST_ASSERT_NOT_NULL(tokens);
    TEST_ASSERT_EQUAL_STRING("mondo", (char *)tokens->content);
    tokens = tokens->next;

    // Nessun altro token
    TEST_ASSERT_NULL(tokens);
    free_raw_tokens(&tokens);
}

void test_tokenizer_spaces(void)
{
    const char *input = "   ls    -la  ";
    t_list *tokens = tokenize(input);

    TEST_ASSERT_NOT_NULL(tokens);
    TEST_ASSERT_EQUAL_STRING("ls", tokens->content);
    tokens = tokens->next;

    TEST_ASSERT_NOT_NULL(tokens);
    TEST_ASSERT_EQUAL_STRING("-la", tokens->content);
    tokens = tokens->next;

    TEST_ASSERT_NULL(tokens); // Solo 2 token

    // cleanup
    free_raw_tokens(&tokens);
}

void test_tokenize_empty_string(void)
{
    const char *input = "";
    t_list *tokens = tokenize(input);

    TEST_ASSERT_NULL(tokens); // Nessun token atteso
}

void test_tokenize_only_spaces(void)
{
    const char *input = "     ";
    t_list *tokens = tokenize(input);
    TEST_ASSERT_NULL(tokens);  // Nessun token
}

void test_tokenize_null_input(void)
{
    t_list *tokens = tokenize(NULL);

    TEST_ASSERT_NULL(tokens); // Protezione da input NULL (se gestita)
}

void test_tokenize_quoted_escaped_string(void)
{
    const char *input = "echo \"ciao mondo\"";
    t_list *tokens = tokenize(input);

    TEST_ASSERT_EQUAL_STRING("echo", tokens->content);
    tokens = tokens->next;
    TEST_ASSERT_EQUAL_STRING("ciao mondo", tokens->content); // Le virgolette fanno un token unico
    tokens = tokens->next;

    TEST_ASSERT_NULL(tokens);

    free_raw_tokens(&tokens);
}

void test_tokenize_mixed_quotes_concat(void)
{
    const char *input = "echo \"ciao'\"\"\"\"mondo\"";
    t_list *tokens = tokenize(input);

    // Primo token: echo
    TEST_ASSERT_NOT_NULL(tokens);
    TEST_ASSERT_EQUAL_STRING("echo", tokens->content);
    tokens = tokens->next;

    // Secondo token: ciao'mondo
    TEST_ASSERT_NOT_NULL(tokens);
    TEST_ASSERT_EQUAL_STRING("ciao'mondo", tokens->content);
    tokens = tokens->next;

    // Nessun altro token
    TEST_ASSERT_NULL(tokens);
    
    // Cleanup
    free_raw_tokens(&tokens);
}

void test_tokenize_special_symbols(void)
{
    const char *input = "cat file.txt | grep keyword > out.txt";
    t_list *tokens = tokenize(input);

    TEST_ASSERT_EQUAL_STRING("cat", tokens->content);
    tokens = tokens->next;
    TEST_ASSERT_EQUAL_STRING("file.txt", tokens->content);
    tokens = tokens->next;
    TEST_ASSERT_EQUAL_STRING("|", tokens->content);
    tokens = tokens->next;
    TEST_ASSERT_EQUAL_STRING("grep", tokens->content);
    tokens = tokens->next;
    TEST_ASSERT_EQUAL_STRING("keyword", tokens->content);
    tokens = tokens->next;
    TEST_ASSERT_EQUAL_STRING(">", tokens->content);
    tokens = tokens->next;
    TEST_ASSERT_EQUAL_STRING("out.txt", tokens->content);
    tokens = tokens->next;

    TEST_ASSERT_NULL(tokens);

    free_raw_tokens(&tokens);
}

void test_tokenize_attached_symbols(void)
{
    const char *input = "ls|grep";
    t_list *tokens = tokenize(input);

    TEST_ASSERT_EQUAL_STRING("ls", tokens->content);
    tokens = tokens->next;
    TEST_ASSERT_EQUAL_STRING("|", tokens->content);
    tokens = tokens->next;
    TEST_ASSERT_EQUAL_STRING("grep", tokens->content);
    tokens = tokens->next;

    TEST_ASSERT_NULL(tokens);

    free_raw_tokens(&tokens);
}

// echo \"ciao mondo (tratta \" come carattere)
void test_tokenize_unclosed_escaped_double_quote(void)
{
    const char *input = "echo \\\"ciao mondo";
    printf("input: %s\n", input);
    t_list *tokens = tokenize(input);

    TEST_ASSERT_EQUAL_STRING("echo", tokens->content);
    tokens = tokens->next;
    TEST_ASSERT_EQUAL_STRING("\"ciao mondo", tokens->content);
    tokens = tokens->next;

    TEST_ASSERT_NULL(tokens);

    free_raw_tokens(&tokens);
}

//  echo "ciao mondo (" apre una stringa, input multilinea)
void test_tokenize_unclosed_double_quote_should_error(void)
{
    const char *input = "echo \"ciao mondo";
    printf("input: %s\n", input);
    t_list *tokens = tokenize(input);

    // (restituisce errore)
    TEST_ASSERT_NULL(tokens);

    free_raw_tokens(&tokens);
}

void test_tokenize_pipeline_no_spaces(void)
{
    const char *input = "echo ciao|grep ciao";
    t_list *tokens = tokenize(input);

    // 1. echo
    TEST_ASSERT_NOT_NULL(tokens);
    TEST_ASSERT_EQUAL_STRING("echo", tokens->content);
    tokens = tokens->next;

    // 2. ciao
    TEST_ASSERT_NOT_NULL(tokens);
    TEST_ASSERT_EQUAL_STRING("ciao", tokens->content);
    tokens = tokens->next;

    // 3. |
    TEST_ASSERT_NOT_NULL(tokens);
    TEST_ASSERT_EQUAL_STRING("|", tokens->content);
    tokens = tokens->next;

    // 4. grep
    TEST_ASSERT_NOT_NULL(tokens);
    TEST_ASSERT_EQUAL_STRING("grep", tokens->content);
    tokens = tokens->next;

    // 5. ciao
    TEST_ASSERT_NOT_NULL(tokens);
    TEST_ASSERT_EQUAL_STRING("ciao", tokens->content);
    tokens = tokens->next;

    TEST_ASSERT_NULL(tokens);

    free_raw_tokens(&tokens);
}
