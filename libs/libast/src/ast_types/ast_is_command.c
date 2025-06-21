#include "ast.h"

int ast_is_command(const t_ast *node)
{
	printf("is command %d\n", node && node->type == AST_COMMAND);
	return (node && node->type == AST_COMMAND);
}
