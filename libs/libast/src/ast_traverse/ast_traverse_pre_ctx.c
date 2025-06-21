/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_traverse_pre_ctx.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 22:36:31 by sabruma           #+#    #+#             */
/*   Updated: 2025/06/21 22:36:31 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

// pre-traversal
void	astt_pre_ctx(t_ast *node, void (*visit)(t_ast *, void *), void *data)
{
	if (!node || !visit)
		return ;
	visit(node, data);
	astt_pre_ctx(node->left, visit, data);
	astt_pre_ctx(node->right, visit, data);
}
