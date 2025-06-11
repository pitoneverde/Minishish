#include "ast.h"

void ast_traverse_post_ctx(t_ast *node, void (*visit)(t_ast *, void *), void *data)
{
	if (!node || !visit)
		return;
	ast_traverse_post_ctx(node->left, visit, data);
	ast_traverse_post_ctx(node->right, visit, data);
	visit(node, data);
}

// void ast_traverse_level(t_ast *node, void (*visit)(t_ast *))
// {
// 	visit(node);
// }