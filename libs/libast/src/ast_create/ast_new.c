#include "ast.h"

t_ast *ast_new(t_ast_type type, char *value)
{
	t_ast *node;

	node = (t_ast *)malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = type;
	node->value = NULL;
	node->left = NULL;
	node->right = NULL;
	node->error = NULL;
	node->argv = NULL;
	if (value)
		node->value = ft_strdup(value);
	return (node);
}