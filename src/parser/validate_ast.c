/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_ast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:28:48 by sabruma           #+#    #+#             */
/*   Updated: 2025/07/09 18:43:45 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_ast	*validate_ast_node(t_ast *node);

void	validate_ast(t_ast **root)
{
	if (!root)
		return ;
	astt_post_rpl(root, validate_ast_node);
}

static t_ast	*validate_ast_node(t_ast *node)
{
	if (!node || ast_has_error(node))
		return (node);
	if (!ast_is_valid(node))
	{
		if (node->value)
			return (syntax_error_token(node->value));
		else
			return (syntax_error_token("newline"));
	}
	return (node);
}
