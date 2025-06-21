/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_filter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 22:20:29 by sabruma           #+#    #+#             */
/*   Updated: 2025/06/21 22:21:22 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

// Same as _n version but the array is NULL-terminated
// Doesn't support NULL elements
// Avoids to free data but frees the list nodes (shared ownership)
t_ast	**ast_filter(t_ast *root, int (*predicate)(const t_ast *))
{
	t_ast				**result;
	size_t				len;
	t_ast_filter_ctx	ctx;

	if (!root)
		return (NULL);
	ctx.predicate = predicate;
	ctx.matches = NULL;
	astt_pre_ctx(root, ast_filter_visit, &ctx);
	result = (t_ast **)lst_to_array_ex(ctx.matches, &len, 1);
	ft_lstclear(&ctx.matches, NULL);
	if (len == 0)
		return (free(result), NULL);
	return (result);
}

// obsolete after filter util
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