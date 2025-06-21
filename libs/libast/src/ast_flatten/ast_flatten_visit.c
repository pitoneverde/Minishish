/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_flatten_visit.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 22:34:49 by sabruma           #+#    #+#             */
/*   Updated: 2025/06/21 22:34:49 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

void	ast_flatten_visit(t_ast *node, void *ctx)
{
	t_list	**nodes;

	nodes = (t_list **)ctx;
	ft_lstadd_back(nodes, ft_lstnew(node));
}
