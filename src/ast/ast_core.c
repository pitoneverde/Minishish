#include "ast.h"
#include "matrix_helpers.h"

void	ast_attach_left(t_ast *parent, t_ast *child)
{
	if (parent)
		parent->left = child;
}

void	ast_attach_right(t_ast *parent, t_ast *child)
{
	if (parent)
		parent->right = child;
}

void	free_ast(t_ast *tree)
{
	if (!tree)
		return ;
	free_ast(tree->left);
	free_ast(tree->right);
	if (tree->value)
		free(tree->value);
	if (tree->error)
		free(tree->error);
	if (tree->argv)
		mtxfree_str(tree->argv);
	free(tree);
}

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