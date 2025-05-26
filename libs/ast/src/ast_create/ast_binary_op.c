#include "ast.h"

t_ast *ast_binary_op(t_ast_type type, char *op, t_ast *left, t_ast *right)
{
	t_ast *opnode = ast_new(type, op);
	if (!opnode)
		return (free_ast(left), free_ast(right), NULL);
	opnode->left = left;
	opnode->right = right;
	return (opnode);
}
