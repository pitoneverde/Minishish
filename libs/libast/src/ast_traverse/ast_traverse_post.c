/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_traverse_post.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 22:36:14 by sabruma           #+#    #+#             */
/*   Updated: 2025/06/21 22:36:15 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

// post-traversal
void	astt_post(t_ast *node, void (*visit)(t_ast *))
{
	if (!node || !visit)
		return ;
	astt_post(node->left, visit);
	astt_post(node->right, visit);
	visit(node);
}
