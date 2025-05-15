#include "minishell.h"

t_ast *parse(t_list *tokens)
{
	return parse_expression(&tokens);
}