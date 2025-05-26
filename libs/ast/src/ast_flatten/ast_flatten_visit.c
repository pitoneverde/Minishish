#include "ast.h"

void ast_flatten_visit(t_ast *node, void *ctx)
{
	t_list **nodes = (t_list **)ctx;
	ft_lstadd_back(nodes, ft_lstnew(node));
}
