/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_traverse_pre.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 22:36:42 by sabruma           #+#    #+#             */
/*   Updated: 2025/06/21 22:36:43 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

// pre-traversal
void	astt_pre(t_ast *node, void (*visit)(t_ast *))
{
	if (!node || !visit)
		return ;
	visit(node);
	astt_pre(node->left, visit);
	astt_pre(node->right, visit);
}
