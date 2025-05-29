#include "ast.h"

// something like: "< file1 > file2 >> file3"
int ast_is_redirection_chain(const t_ast *node)
{
	if (!node)
		return (0);
	if (ast_is_redirection(node))
		return (ast_is_redirection_chain(node->right));
	return (0);
}
