/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_has_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 22:49:36 by sabruma           #+#    #+#             */
/*   Updated: 2025/07/09 19:52:01 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

int	ast_has_error(const t_ast *node)
{
	if (!node)
		return (0);
	if (node && (node->type == AST_ERROR || node->error != NULL))
		return (1);
	if (ast_is_operator(node))
		return (ast_has_error(node->left) || ast_has_error(node->right));
	return (0);
}
