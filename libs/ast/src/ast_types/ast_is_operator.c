#include "ast.h"

int ast_is_operator(const t_ast *node)
{
	return (node && (node->type == AST_APPEND || node->type == AST_HEREDOC
		|| node->type == AST_PIPE || node->type == AST_REDIR_IN
		|| node->type == AST_REDIR_OUT));
}