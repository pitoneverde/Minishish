#include "ast.h"

void ast_traverse_post(t_ast *node, void (*visit)(t_ast *))
{
	if (!node || !visit)
		return;
	ast_traverse_post(node->left, visit);
	ast_traverse_post(node->right, visit);
	visit(node);
}
