#include "minishell.h"
#include "expansion.h"

// // Mock shell and env lookup
// char *get_env_value(char **env, const char *key)
// {
// 	size_t len = ft_strlen(key);
// 	for (int i = 0; env && env[i]; i++) {
// 		if (!ft_strncmp(env[i], key, len) && env[i][len] == '=')
// 			return env[i] + len + 1;
// 	}
// 	return NULL;
// }

// Recursive AST command printer
void	print_ast_commands(t_ast *node)
{
	if (!node)
		return;
	if (node->type == AST_COMMAND)
	{
		printf("Expanded command:");
		switch (node->quote)
		{
		case S_QUOTE:
			printf("S_QUOTE");
			break;
		case D_QUOTE:
			printf("D_QUOTE");
			break;
		default:
			printf("N_QUOTE");
			break;
		}
		for (int i = 0; i < node->argc; i++)
			printf("  argv[%d]: [%s]\n", i, node->argv[i]);
	}
	print_ast_commands(node->left);
	print_ast_commands(node->right);
}

int	main(int argc, char **argv, char **envp)
{
	t_sh	shell;
	t_ast	*ast;
	char	input[1024];

	(void)argc;
	(void)argv;

	// Setup shell context
	shell.env = envp_to_env(envp);
	shell.last_code = 42;

	while (1)
	{
		printf("expander$ ");
		if (!fgets(input, sizeof(input), stdin))
			break;

		// remove newline
		input[strcspn(input, "\n")] = '\0';
		if (ft_strlen(input) == 0)
			continue;

		ast = read_command_line(input);
		if (!ast)
		{
			printf("Parse error.\n");
			continue;
		}
		print_ast(ast, 0);
		expand_ast(ast, &shell);
		print_ast(ast, 0);
		// print_ast_commands(ast);
		ast_free(ast); // You should already have this
	}
	return (0);
}
