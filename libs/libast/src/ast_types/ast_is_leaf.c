#include "ast.h"

int ast_is_leaf(const t_ast *node)
{
	return (!node->left && !node->right);
}