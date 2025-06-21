/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_traverse_post_ctx.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 22:35:43 by sabruma           #+#    #+#             */
/*   Updated: 2025/06/21 22:35:50 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

// post-traversal
void	astt_post_ctx(t_ast *node, void (*visit)(t_ast *, void *), void *data)
{
	if (!node || !visit)
		return ;
	astt_post_ctx(node->left, visit, data);
	astt_post_ctx(node->right, visit, data);
	visit(node, data);
}
