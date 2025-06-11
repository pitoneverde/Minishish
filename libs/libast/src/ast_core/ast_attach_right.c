#include "ast.h"

void ast_attach_right(t_ast *parent, t_ast *child)
{
	if (parent)
		parent->right = child;
}