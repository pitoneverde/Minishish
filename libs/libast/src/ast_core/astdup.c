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
	if (node->quote)
		clone->quote = node->quote;
	if (node->args)
		clone->args = ft_lstmap(node->args, (void *(*)(void *))astdup, ast_free_void);
	clone->argc = node->argc;
	clone->left = astdup(node->left);
	clone->right = astdup(node->right);
	return (clone);
}