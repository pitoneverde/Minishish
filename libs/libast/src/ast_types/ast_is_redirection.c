#include "ast.h"

int ast_is_redirection(const t_ast *node)
{
	return (node->type == AST_REDIR_IN || node->type == AST_REDIR_OUT
		|| node->type == AST_HEREDOC || node->type == AST_APPEND);
}