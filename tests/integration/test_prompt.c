#include "helpers.h"

/* include la vera main ma rinominata */
extern int real_main(int, const char **, const char **);

/* ---------- stub readline / add_history ---------- */

/* Lista di risposte simulate da readline() */
static const char *readline_script[16] = { NULL };
static int readline_index = 0;

char *readline(const char *prompt)
{
    if (prompt)
        write(STDOUT_FILENO, prompt, strlen(prompt));

    const char *response = readline_script[readline_index++];
    if (!response)
        return NULL;
    return strdup(response);
}

void add_history(const char *s) { (void)s; }

/* Utility per impostare il comportamento finto di readline */
static void set_readline_script(const char **script)
{
    for (int i = 0; i < 16; i++)
        readline_script[i] = script[i];
    readline_index = 0;
}

/* ---------- TEST 1: prompt + Ctrl-D immediato (una stampa) ---------- */
void test_prompt_ctrl_d_subito(void)
{
    const char *script[] = { NULL };  // Ctrl-D subito
    set_readline_script(script);

    redirect_stdout_begin();

    const char *argv[] = { "./minishell", NULL };
    const char *envp[] = { NULL };
    int ret = real_main(1, argv, envp);

    char *out = redirect_stdout_end();

    TEST_ASSERT_EQUAL_STRING("> exit\n", out);
    TEST_ASSERT_EQUAL_INT(0, ret);
}

/* ---------- TEST 2: prompt, riga vuota, prompt, Ctrl-D (due stampe) ---------- */
void test_prompt_empty_then_eof(void)
{
    const char *script[] = { "", NULL };  // Invio vuoto, poi Ctrl-D
    set_readline_script(script);

    redirect_stdout_begin();

    const char *argv[] = { "./minishell", NULL };
    const char *envp[] = { NULL };
    int ret = real_main(1, argv, envp);

    char *out = redirect_stdout_end();

    TEST_ASSERT_EQUAL_STRING("> > exit\n", out);
    TEST_ASSERT_EQUAL_INT(0, ret);
}
