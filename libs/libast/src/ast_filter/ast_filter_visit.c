/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_filter_visit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 22:22:20 by sabruma           #+#    #+#             */
/*   Updated: 2025/06/21 22:23:04 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

// wraps the t_ast nodes into t_list to filter
void	ast_filter_visit(t_ast *node, void *data)
{
	t_ast_filter_ctx	*ctx;

	ctx = (t_ast_filter_ctx *)data;
	if (ctx->predicate(node))
		ft_lstadd_back(&ctx->matches, ft_lstnew(node));
}
