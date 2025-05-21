#include "ast.h"

int ast_is_operator(t_ast_type type)
{
	return (type == AST_APPEND || type == AST_HEREDOC
		|| type == AST_PIPE || type == AST_REDIR_IN
		|| type == AST_REDIR_OUT);
}

int ast_is_command(const t_ast *node)
{
	return (node && node->type == AST_COMMAND);
}

int ast_is_simple_pipeline(const t_ast *node)
{
	if (node && node->type == AST_PIPE)
		return (node->left && ast_is_command(node->left)
			&& node->right && ast_is_command(node->right));
	return (0);
}

// something like: "< file1 > file2 >> file3"
int ast_is_redirection_chain(const t_ast *node)
{
	if (!node)
		return (0);
	if (node->type == AST_REDIR_IN || node->type == AST_REDIR_OUT
		|| node->type == AST_HEREDOC || node->type == AST_APPEND)
		return (ast_is_redirection_chain(node->right));
	return (0);
}
