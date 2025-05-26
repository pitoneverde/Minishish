#include "ast.h"

// behaves like foreach
void ast_map(t_ast *node, void (*f)(t_ast *))
{
	if (!node || !f)
		return;
	f(node);
	ast_map(node->left, f);
	ast_map(node->right, f);
}
