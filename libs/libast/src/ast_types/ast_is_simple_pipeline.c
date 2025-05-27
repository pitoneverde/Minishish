#include "ast.h"

int ast_is_simple_pipeline(const t_ast *node)
{
	if (node && node->type == AST_PIPE)
		return (node->left && ast_is_command(node->left)
			&& node->right && ast_is_command(node->right));
	return (0);
}
