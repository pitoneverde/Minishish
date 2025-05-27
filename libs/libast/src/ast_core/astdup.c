#include "ast.h"

t_ast *astdup(const t_ast *node)
{
	t_ast *clone;

	if (!node)
		return (NULL);
	if (node->value)
		clone = ast_new(node->type, node->value);
	else
		clone = ast_new(node->type, NULL);
	if (node->argv)
		clone->argv = mtxdup_str(node->argv);
	if (node->error)
		clone->error = ft_strdup(node->error);
	clone->left = astdup(node->left);
	clone->right = astdup(node->right);
	return (clone);
}