#include "ast.h"

// Core filter: returns array of the nodes matching predicate.
// Count is the number of matches
t_ast **ast_filter_n(t_ast *root, int (*predicate)(const t_ast *), size_t *dim)
{
	t_ast **result;
	size_t len;
	t_ast_filter_ctx ctx;

	if (dim)
		*dim = 0;
	if (!root)
		return (NULL);
	ctx.predicate = predicate;
	ctx.matches = NULL;
	ast_traverse_pre_ctx(root, ast_filter_visit, &ctx);
	result = (t_ast **)lst_to_array_ex(ctx.matches, &len, 0);
	ft_lstclear(&ctx.matches, NULL);
	if (dim)
		*dim = len;
	if (len == 0)
		return (free(result), NULL);
	return (result);
}