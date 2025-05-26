#include "ast.h"

void ast_free_void(void *tree)
{
	ast_free((t_ast *)tree);
}