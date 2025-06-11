#include "helpers.h"

/* definizione della variabile globale dichiarata in helpers.h */
int g_readline_calls = 0;

/* unico setUp / tearDown visibile a TUTTO il runner Unity */
void setUp(void)
{
    reset_readline_counter();      /* azzera il contatore dello stub */
}

void tearDown(void)
{
}
