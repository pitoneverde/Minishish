#include "ast.h"

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
		mtxfree((void **)tree->argv,
			count_matrix((void **)tree->argv), free_string);
	free(tree);
}
