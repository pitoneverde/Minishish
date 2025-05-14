#include "minishell.h"
#include "unity.h"

#include <string.h>
#include <stdio.h>

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

void test_main_stampa_ciao(void)
{
    int ret = real_main();
    TEST_ASSERT_EQUAL_INT(0, ret); // testa return main 0
    fflush(stdout);

    /* Leggi ciò che real_main ha scritto nel temporaneo. */
    fflush(tmp_fp);
    rewind(tmp_fp);

    char buffer[64] = {0};
    size_t n = fread(buffer, 1, sizeof(buffer)-1, tmp_fp);

    fprintf(stderr, "DEBUG len=%zu  HEX:", n);
    for (size_t i = 0; buffer[i]; ++i)
        fprintf(stderr, " %02X", (unsigned char)buffer[i]);
    fprintf(stderr, "  STRINGA:[%s]\n", buffer);

    /* Accetta sia "ciao\n" sia "ciao\r\n" */
    TEST_ASSERT_TRUE_MESSAGE(
        strcmp(buffer, "ciao\n")  == 0,
        "Output diverso da 'ciao\\n'"
    );
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_main_stampa_ciao);
    return UNITY_END();
}