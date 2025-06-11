#include "ast.h"

// SYNTAX CHECK
int ast_is_valid(const t_ast *node)
{
	if (!node || ast_has_error(node))
		return (0);
	if (node->type == AST_COMMAND)
		return (node->argv != NULL && node->argv[0] != NULL);
	else if (node->type == AST_LITERAL)
		return (node->value != NULL);
	else if (node->type == AST_PIPE)
		return (ast_is_valid(node->left) && ast_is_valid(node->right));
	else if (node->type == AST_REDIR_IN || node->type == AST_REDIR_OUT ||
			node->type == AST_APPEND || node->type == AST_HEREDOC)
		return (node->left && node->right
			&& ast_is_valid(node->left)
			&& node->right->type == AST_LITERAL
			&& ast_is_valid(node->right));
	else
		return (0);
}