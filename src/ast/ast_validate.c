#include "ast.h"

int ast_has_error(const t_ast *node)
{
	if (!node)
		return 0;
	if (node->type == AST_ERROR || node->error != NULL)
		return 1;
	return ast_has_error(node->left) || ast_has_error(node->right);
}

int ast_is_valid(const t_ast *node)
{
	(void)node;
	return 1;
}