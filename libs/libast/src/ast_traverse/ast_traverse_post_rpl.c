/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_traverse_post_rpl.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:24:07 by sabruma           #+#    #+#             */
/*   Updated: 2025/07/10 16:53:32 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

// can modify the ast structure (use with caution!)
void	astt_post_rpl(t_ast **node, t_ast *(*visit)(t_ast *))
{
	t_ast	*new_node;

	if (!node || !*node)
		return ;
	printf("Entering node: %s\n", (*node)->value);
	astt_post_rpl(&(*node)->left, visit);
	astt_post_rpl(&(*node)->right, visit);
	new_node = visit(*node);
	if (new_node != NULL)
		ast_replace_subtree(node, new_node);
	// else if (new_node == NULL)
	// 	fprintf(stderr, "WARN: visit() returned NULL — not replacing\n");
	// printf("\n\nNODE:\n");
	// print_ast(*node, 0);
	// printf("\n\nnewNODE:\n");
	// print_ast(new_node, 0);
}