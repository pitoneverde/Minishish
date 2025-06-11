#include "ast.h"

int ast_is_command(const t_ast *node)
{
	return (node && node->type == AST_COMMAND);
}
