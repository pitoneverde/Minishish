#include "expansion.h"
#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

// Entry point to test read_heredoc with real expansion and shell env
int main(void)
{
	t_sh shell;
	shell.env = NULL;
	shell.last_code = 0;
	shell.is_interactive = 1;

	// Add env var $FOO = "bar"
	set_env_var(&shell.env, "FOO", "bar", 1);

	// Unquoted heredoc (should expand $FOO)
	printf("Unquoted heredoc test (<<EOF):\n");
	char *res1 = read_heredoc("EOF", N_QUOTE, &shell);
	printf("--- Result ---\n%s--- End ---\n", res1);
	free(res1);

	// Double-quoted heredoc (no expansion)
	printf("\nDouble-quoted heredoc test (<<\"EOF\"):\n");
	char *res2 = read_heredoc("EOF", D_QUOTE, &shell);
	printf("--- Result ---\n%s--- End ---\n", res2);
	free(res2);

	// Single-quoted heredoc (no expansion)
	printf("\nSingle-quoted heredoc test (<<'EOF'):\n");
	char *res3 = read_heredoc("EOF", S_QUOTE, &shell);
	printf("--- Result ---\n%s--- End ---\n", res3);
	free(res3);

	// Cleanup
	free_env(shell.env);
	return 0;
}
