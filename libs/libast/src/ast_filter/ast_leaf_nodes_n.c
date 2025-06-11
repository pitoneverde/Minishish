#include "ast.h"

t_ast **ast_leaf_nodes_n(t_ast *root, size_t *dim)
{
	return ast_filter_n(root, ast_is_leaf, dim);
}