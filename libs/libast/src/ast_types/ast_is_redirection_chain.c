#include "ast.h"

// something like: "< file1 > file2 >> file3"
int ast_is_redirection_chain(const t_ast *node)
{
	if (!node)
		return (0);
	if (node->type == AST_REDIR_IN || node->type == AST_REDIR_OUT
		|| node->type == AST_HEREDOC || node->type == AST_APPEND)
		return (ast_is_redirection_chain(node->right));
	return (0);
}
