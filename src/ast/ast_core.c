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
	free(tree->value);
	free(tree->error);
	free_char_matrix(tree->argv);
	free(tree);
}

void free_char_matrix(char **matrix)
{
	int i;

	if (!matrix)
		return ;
	i = 0;
	while (matrix[i])
		free(matrix[i++]);
	free(matrix);
}