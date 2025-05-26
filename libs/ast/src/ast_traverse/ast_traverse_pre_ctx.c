#include "ast.h"

void ast_traverse_pre_ctx(t_ast *node, void (*visit)(t_ast *, void *), void *data)
{
	if (!node || !visit)
		return;
	visit(node, data);
	ast_traverse_pre_ctx(node->left, visit, data);
	ast_traverse_pre_ctx(node->right, visit, data);
}
