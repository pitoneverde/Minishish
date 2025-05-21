#include "helpers.h"

/* include la vera main ma rinominata */
extern int real_main(int, const char **, const char **);

/* ---------- stub readline / add_history ---------- */
char *readline(const char *prompt)
{
    write(STDOUT_FILENO, prompt, strlen(prompt));     /* stampa il prompt */

    /* prima chiamata → stringa vuota, seconda → NULL (Ctrl-D) */
    if (g_readline_calls++ == 0)
        return strdup("");        /* Invio senza comando          */
    return NULL;                  /* EOF: la shell termina        */
}
void add_history(const char *s) { (void)s; }

/* ---------- TEST 1: prompt + Ctrl-D immediato (una stampa) ---------- */
void test_prompt_ctrl_d_subito(void)
{
    redirect_stdout_begin();

    const char *argv[] = { "./minishell", NULL };
    const char *envp[] = { NULL };
    int ret = real_main(1, argv, envp);

    char *out = redirect_stdout_end();

    // bash-like: prompt + "exit\n"
    TEST_ASSERT_EQUAL_STRING("> exit\n", out);
    TEST_ASSERT_EQUAL_INT(0, ret);
}

/* ---------- TEST 2: prompt, riga vuota, prompt, Ctrl-D (due stampe) ---------- */
void test_prompt_empty_then_eof(void)
{
    g_readline_calls = 0;                 // reset chiamate stub
    
    /* reinizializzato in setUp() grazie a reset_readline_counter() */
    redirect_stdout_begin();

    const char *argv[] = { "./minishell", NULL };
    const char *envp[] = { NULL };
    int ret = real_main(1, argv, envp);

    char *out = redirect_stdout_end();
    TEST_ASSERT_EQUAL_STRING("> > exit\n", out);
    TEST_ASSERT_EQUAL_INT(0, ret);
}
