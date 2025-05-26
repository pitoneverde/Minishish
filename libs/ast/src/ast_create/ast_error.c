#include "ast.h"

t_ast *ast_error(char *msg)
{
	t_ast *error_node = ast_new(AST_ERROR, NULL);
	if (!error_node)
		return (NULL);
	error_node->error = ft_strdup(msg);
	if (!error_node->error)
		return (free_ast(error_node), NULL);
	return (error_node);
}
