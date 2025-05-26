#include "ast.h"

char *ast_to_string(const t_ast *node)
{
	t_ast *clone;
	char *res;

	clone = astdup(node);
	if (!clone)
		return (NULL);
	ast_stringify(clone);
	if (!clone->value)
		return (free_ast(clone), NULL);
	res = ft_strdup(clone->value);
	return (free_ast(clone), res);
}
