/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_traverse_post_rpl.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:24:07 by sabruma           #+#    #+#             */
/*   Updated: 2025/07/09 19:23:33 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

// can modify the ast structure (use with caution!)
void	astt_post_rpl(t_ast **node, t_ast *(*visit)(t_ast *))
{
	t_ast	*new_node;

	if (!node || !*node)
		return ;
	astt_post_rpl(&(*node)->left, visit);
	astt_post_rpl(&(*node)->right, visit);
	new_node = visit(*node);
	if (new_node != NULL && new_node != *node)
		ast_replace_subtree(node, new_node);
}