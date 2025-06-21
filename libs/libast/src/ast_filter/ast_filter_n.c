/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_filter_n.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 22:23:43 by sabruma           #+#    #+#             */
/*   Updated: 2025/06/21 22:25:06 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

// Core filter: returns array of the nodes matching pred.
// Count is the number of matches
t_ast	**ast_filter_n(t_ast *root, int (*pred)(const t_ast *), size_t *dim)
{
	t_ast				**result;
	size_t				len;
	t_ast_filter_ctx	ctx;

	if (dim)
		*dim = 0;
	if (!root)
		return (NULL);
	ctx.predicate = pred;
	ctx.matches = NULL;
	astt_pre_ctx(root, ast_filter_visit, &ctx);
	result = (t_ast **)lst_to_array_ex(ctx.matches, &len, 0);
	ft_lstclear(&ctx.matches, NULL);
	if (dim)
		*dim = len;
	if (len == 0)
		return (free(result), NULL);
	return (result);
}
