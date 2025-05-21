#include "ast.h"

void ast_traverse_pre(t_ast *node, void (*visit)(t_ast *))
{
	if (!node || !visit)
		return ;
	visit(node);
	ast_traverse_pre(node->left, visit);
	ast_traverse_pre(node->right, visit);
}

void ast_traverse_post(t_ast *node, void (*visit)(t_ast *))
{
	if (!node || !visit)
		return;
	ast_traverse_post(node->left, visit);
	ast_traverse_post(node->right, visit);
	visit(node);
}

void ast_traverse_level(t_ast *node, void (*visit)(t_ast *))
{
	visit(node);
}