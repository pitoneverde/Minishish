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

char *readline(const char *prompt)
{
    static int call_no = 0;

    write(STDOUT_FILENO, prompt, strlen(prompt));   /* stampa prompt */

    if (call_no++ == 0)
        return strdup("");      /* simuliamo Invio senza comando */
    return NULL;                /* simuliamo Ctrl-D --> minishell termina */
}
void add_history(const char *s) { (void)s; }

void setUp(void)
{
    // Salva e reindirizza stdout SOLO per main
    stdout_backup = dup(STDOUT_FILENO);   // 1. salva fd fi stdout
    tmp_fp = tmpfile();                   // 2. crea file temporaneo
    dup2(fileno(tmp_fp), STDOUT_FILENO);  // 3. tutto cio' che verrebbe stampato in stdout finische nel file
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
    TEST_ASSERT_EQUAL_STRING("Wrong number of arguments\n", buf);
    TEST_ASSERT_EQUAL_INT(0, ret);
}

void test_prompt_then_ctrl_d(void)
{
    const char *argv[] = { "./minishell", NULL };
    const char *envp[] = { NULL };

    /* Lancia la shell (una sola iterazione) */
    int ret = real_main(1, argv, envp);

    /* Leggi tutto ciò che è stato scritto su stdout */
    fflush(tmp_fp);
    rewind(tmp_fp);

    char buf[64] = {0};
    size_t n = fread(buf, 1, sizeof(buf)-1, tmp_fp);
    buf[n] = '\0';

    /* Ci aspettiamo esattamente "> > " (prompt mostrato due volte)     *
     *    1) all’avvio, 2) prima di ricevere NULL e uscire.            */
    TEST_ASSERT_EQUAL_STRING("> > ", buf);

    /* Il programma deve essere uscito con 0 */
    TEST_ASSERT_EQUAL_INT(0, ret);
}

void test_prompt_e_exit(void)
{
    const char *argv[] = { "./minishell", NULL };
    const char *envp[] = { NULL };

    int ret = real_main(1, argv, envp);

    /* Leggi tutto l’output */
    fflush(tmp_fp);
    rewind(tmp_fp);
    char buf[64] = {0};
    fread(buf, 1, sizeof(buf)-1, tmp_fp);

    /* Bash mostra:  "> "  (prompt)  poi  "exit\n" */
    TEST_ASSERT_EQUAL_STRING("> exit\n", buf);
    TEST_ASSERT_EQUAL_INT(0, ret);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_main_argc_diverso_da_1);
    RUN_TEST(test_prompt_then_ctrl_d);
    RUN_TEST(test_prompt_e_exit);
    return UNITY_END();
}