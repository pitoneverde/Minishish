#include "expansion.h"

// $var -> $var value
// Core expansion entry point
void	expand_ast(t_ast *root, t_sh *shell)
{
	ast_traverse_post_ctx(root, should_expand_token, shell);
}

void	should_expand_token(t_ast *node, void *ctx)
{
	t_sh	*shell;

	shell = (t_sh *)ctx;
	if (!node)
		return ;
	if (node->type == AST_COMMAND)
		expand_command_args(node, shell);
	else if (node->value && node->quote != S_QUOTE)
		expand_token_value(node, shell);
}

// Handles heredoc input, expands lines only if delimiter is unquoted
char	*read_heredoc(const char *delimiter, t_quote_type quote, t_sh *shell)
{
	(void)delimiter;
	(void)quote;
	(void)shell;
	return (NULL);
}
