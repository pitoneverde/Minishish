#ifndef HELPERS_H
#define HELPERS_H

#include "minishell.h"

#include "unity.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* -------------  stato globale per lo stub di readline ------------- */
extern int g_readline_calls;              /* definito in helpers_setup.c */
static inline void reset_readline_counter(void) { g_readline_calls = 0; }

/* -------------  redirect di STDOUT per un singolo test ------------- */
static int  h_saved_out;
static FILE *tmp_fp;

static inline void redirect_stdout_begin(void)
{
    // Salva fd originale
    h_saved_out = dup(STDOUT_FILENO);
    // Crea un file temporaneo solo per test
    tmp_fp       = tmpfile();
    // Rimpiazza stdout (cio' che doveva andare in stdout andr' in tmp_fp)
    dup2(fileno(tmp_fp), STDOUT_FILENO);
}

static inline char *redirect_stdout_end(void)
{
    // Assicura che tutto ciò che è stato scritto su stdout venga realmente scaricato nel file temporaneo
    fflush(stdout);
    // Ripristina stdout al suo stato originale (il terminale)
    dup2(h_saved_out, STDOUT_FILENO);
    close(h_saved_out);
    // Riavvolge il file temporaneo per leggerlo dall’inizio
    rewind(tmp_fp);
    static char buf[1024];
    size_t n = fread(buf, 1, sizeof(buf) - 1, tmp_fp);
    buf[n] = '\0';
    fclose(tmp_fp);
    return buf;
}

/* -------------  redirect di STDERR per un singolo test ------------- */
static int  h_saved_err;
static FILE *tmp_fp_err;

static inline void redirect_stderr_begin(void)
{
    // Salva fd originale di stderr
    h_saved_err = dup(STDERR_FILENO);
    // Crea file temporaneo per raccogliere l'output di stderr
    tmp_fp_err = tmpfile();
    // Rimpiazza stderr con il file temporaneo
    dup2(fileno(tmp_fp_err), STDERR_FILENO);
}

static inline char *redirect_stderr_end(void)
{
    // Scarica tutto il buffer nel file temporaneo
    fflush(stderr);
    // Ripristina stderr originale
    dup2(h_saved_err, STDERR_FILENO);
    close(h_saved_err);
    // Leggi tutto l'output da stderr
    rewind(tmp_fp_err);
    static char buf[1024];
    size_t n = fread(buf, 1, sizeof(buf) - 1, tmp_fp_err);
    buf[n] = '\0';
    fclose(tmp_fp_err);
    return buf;
}

#endif
