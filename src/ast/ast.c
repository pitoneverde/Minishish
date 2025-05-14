#include "ast.h"

t_ast	*ast_new(t_ast_type type, char *value)
{
	t_ast	*node;

	node = (t_ast *)malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->value = value;
	node->type = type;
	node->left = NULL;
	node->right = NULL;
	node->error = NULL;
	node->argv = NULL;
	return (node);
}

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