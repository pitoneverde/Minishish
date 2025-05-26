#include "ast.h"

// wraps the t_ast nodes into t_list to filter
void ast_filter_visit(t_ast *node, void *data)
{
	t_ast_filter_ctx *ctx = (t_ast_filter_ctx *)data;
	if (ctx->predicate(node))
		ft_lstadd_back(&ctx->matches, ft_lstnew(node));
}
