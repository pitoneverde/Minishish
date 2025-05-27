#include "ast.h"

// search in node->value
int ast_find(t_ast *node, const char *value)
{
	if (!node)
		return (0);
	if (node->value && ft_strncmp(node->value, value, ft_strlen(value)))
		return (1);
	return ast_find(node->left, value) || ast_find(node->right, value);
}
