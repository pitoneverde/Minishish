#include "minishell.h"
#include "unity.h"

#include <string.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

#define main real_main
#include "../../src/main.c"
#undef main

static int  stdout_backup;   // fd originale di STDOUT
static FILE *tmp_fp;         // FILE* associato (per fgets)

void setUp(void)
{
    // Salva e reindirizza stdout SOLO per main
    stdout_backup = dup(STDOUT_FILENO);   // 1. salva stdout

    tmp_fp = tmpfile();                   // 2. crea file temporaneo
    dup2(fileno(tmp_fp), STDOUT_FILENO);  // 3. rimpiazza stdout
}
void tearDown(void)
{
    fflush(stdout);
    dup2(stdout_backup, STDOUT_FILENO);   // ripristina stdout
    close(stdout_backup);
    fclose(tmp_fp);                       // chiude & elimina temp
}
/*
void test_main_stampa_ciao(void)
{
    int ret = real_main();
    TEST_ASSERT_EQUAL_INT(0, ret); // testa return main 0
    fflush(stdout);

    fflush(tmp_fp);
    rewind(tmp_fp);

    char buffer[64] = {0};
    size_t n = fread(buffer, 1, sizeof(buffer)-1, tmp_fp);

    fprintf(stderr, "DEBUG len=%zu  HEX:", n);
    for (size_t i = 0; buffer[i]; ++i)
        fprintf(stderr, " %02X", (unsigned char)buffer[i]);
    fprintf(stderr, "  STRINGA:[%s]\n", buffer);

    TEST_ASSERT_TRUE_MESSAGE(
        strcmp(buffer, "ciao\n")  == 0,
        "Output diverso da 'ciao\\n'"
    );
}*/

void test_main_argc_diverso_da_1(void)
{
    /* 1. prepara argv fittizio con 2 argomenti */
    const char *argv[] = { "./minishell", "ciao", NULL };
    const char *envp[] = { NULL };

    /* 2. cattura stderr in un file temporaneo */
    int saved_stderr = dup(STDERR_FILENO);
    FILE *tmp = tmpfile();
    dup2(fileno(tmp), STDERR_FILENO);

    /* 3. esegui la main “reale” */
    int ret = real_main(2, argv, envp);

    /* 4. ripristina stderr PRIMA di leggere il file, così Unity scrive a video */
    fflush(stderr);
    dup2(saved_stderr, STDERR_FILENO);
    close(saved_stderr);

    /* 5. leggi ciò che è stato stampato da print_error */
    rewind(tmp);
    char buf[64] = {0};
    fgets(buf, sizeof(buf), tmp);
    fclose(tmp);

    /* 6. asserzioni */
    TEST_ASSERT_EQUAL_INT(0, ret);
    TEST_ASSERT_EQUAL_STRING("Wrong number of arguments\n", buf);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_main_argc_diverso_da_1);
    return UNITY_END();
}