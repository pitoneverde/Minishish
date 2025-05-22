#include "ast.h"


// wraps the t_ast nodes into t_list to filter
static void ast_filter_visit(t_ast *node, void *data)
{
	t_ast_filter_ctx *ctx = (t_ast_filter_ctx *)data;
	if (ctx->predicate(node))
		ft_lstadd_back(&ctx->matches, ft_lstnew(node));
}

// Same as _n version but the array is NULL-terminated
// Doesn't support NULL elements
t_ast **ast_filter(t_ast *root, int (*predicate)(const t_ast *))
{
	t_ast				**result;
	size_t				len;
	t_ast_filter_ctx	ctx;

	if (!root)
		return (NULL);
	ctx.predicate = predicate;
	ctx.matches = NULL;
	ast_traverse_pre_ctx(root, ast_filter_visit, &ctx);
	result = (t_ast **)lst_to_array_ex(ctx.matches, &len, 1);
	ft_lstclear(&ctx.matches, NULL);		// very interesting, avoids to free data but frees the list nodes (shared ownership)
	if (len == 0)
		return (free(result), NULL);
	return (result);
}

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
