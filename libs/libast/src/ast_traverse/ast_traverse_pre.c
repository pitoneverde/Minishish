#include "ast.h"

void ast_traverse_pre(t_ast *node, void (*visit)(t_ast *))
{
	if (!node || !visit)
		return;
	visit(node);
	ast_traverse_pre(node->left, visit);
	ast_traverse_pre(node->right, visit);
}
