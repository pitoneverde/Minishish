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

// Equivalent below, without filter utility
int is_leaf_node(const t_ast *node)
{
	return (!node->left && !node->right);
}

t_ast **ast_leaf_nodes(t_ast *root)
{
	return ast_filter(root, ast_is_leaf);
}

t_ast **ast_leaf_nodes_n(t_ast *root, size_t *dim)
{
	return ast_filter_n(root, ast_is_leaf, dim);
}

// // Callback for extracting a leaf node
// static void	collect_leaf_node(t_ast *node, void *ctx)
// {
// 	t_list **leaves = (t_list **)ctx;
// 	if (!node->left && !node->right)
// 		ft_lstadd_back(leaves, ft_lstnew(node));
// }

// // Collects all nodes without children in a NULL-terminated array
// // leaves the tree untouched (shared pointers with arr)
// // free only the array master ptr and then the original tree
// t_ast **ast_leaf_nodes(t_ast *root)
// {
// 	t_ast	**result;
// 	t_list	*leaves;

// 	leaves = NULL;
// 	ast_traverse_pre_ctx(root, collect_leaf_node, &leaves);
// 	result = ast_lst_to_array(leaves);
// 	ft_lstclear(&leaves, NULL);
// 	return (result);
// }

// t_ast **ast_leaf_nodes_n(t_ast *root, size_t *dim)
// {
// 	t_ast **result;
// 	t_list *leaves;

// 	leaves = NULL;
// 	ast_traverse_pre_ctx(root, collect_leaf_node, &leaves);
// 	result = ast_lst_to_array_n(leaves, dim);
// 	ft_lstclear(&leaves, NULL);
// 	return (result);
// }