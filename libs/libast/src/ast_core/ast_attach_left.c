#include "ast.h"

void ast_attach_left(t_ast *parent, t_ast *child)
{
	if (parent)
		parent->left = child;
}