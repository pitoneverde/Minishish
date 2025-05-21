#include "helpers.h"

/* Include la vera main, ma rinominata */
extern int real_main(int, const char **, const char **); 

/* ---------- TEST: argc diverso da 1 ---------- */
void test_argc_troppi(void)
{
    const char *argv[] = { "./minishell", "extra", NULL };
    const char *envp[] = { NULL };

    redirect_stderr_begin();   // intercetta stderr
    redirect_stdout_begin();   // intercetta stdout

    int ret = real_main(2, argv, envp);

    char *err_output = redirect_stderr_end();
    char *out_output = redirect_stdout_end();

    TEST_ASSERT_EQUAL_STRING("Wrong number of arguments\n", err_output);
    TEST_ASSERT_EQUAL_STRING("", out_output); 
    TEST_ASSERT_EQUAL_INT(0, ret);
}
