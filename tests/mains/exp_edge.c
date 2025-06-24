#include <stdio.h>
#include "expansion.h"

int main(void)
{
	t_sh shell;
	char *mock_env[] = {
		"USER=guest",
		"X=1",
		"_VAR=safe",
		"EMPTY=",
		NULL
	};

	const char *cases[] = {
		"$",               // Lone $
		"$?",              // Exit code
		"$UNKNOWN",        // Undefined var
		"$EMPTY",          // Empty var
		"no$var",          // Bad var name (no expansion)
		"$USER",           // Regular
		"${USER}",         // Not supported
		"$_VAR",           // Valid underscore start
		"$1",              // Invalid var (digit)
		"'$USER'",         // Single quoted (no expansion)
		"\"$USER\"",       // Double quoted (should expand)
		"just text",       // No vars
		"$USER$?",         // Combo
		"$$$",             // Edge: multiple $
		NULL
	};

	shell.env = envp_to_env(mock_env);
	shell.last_code = 42;

	for (int i = 0; cases[i]; i++)
	{
		char *expanded = expand_token(cases[i], N_QUOTE, &shell);
		printf("input:    [%s]\n", cases[i]);
		printf("expanded: [%s]\n\n", expanded);
		free(expanded);
	}
	free_env(shell.env);
}
