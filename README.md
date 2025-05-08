# Minishish
mini shell bash
(bash is kept as a reference in is core function in dev)

### Run minishell
make
./minishell

### Run tests
make test



## History
si appoggia a history.h
typedef struct _hist_entry {
    char *line;
    char *data;
} HIST_ENTRY;

extern HIST_ENTRY **the_history; /* array di puntatori     */
extern int history_length;       /* quante voci abbiamo    */
extern int history_base;         /* indice della prima voce
                                    (diverso da 0 se hai
                                     caricato da file)     */