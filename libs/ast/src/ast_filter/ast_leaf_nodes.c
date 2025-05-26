#include "ast.h"

t_ast **ast_leaf_nodes(t_ast *root)
{
	return ast_filter(root, ast_is_leaf);
}