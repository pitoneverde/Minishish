/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_is_simple_pipeline.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 22:45:06 by sabruma           #+#    #+#             */
/*   Updated: 2025/06/21 22:45:09 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

int	ast_is_simple_pipeline(const t_ast *node)
{
	if (node && node->type == AST_PIPE)
		return (node->left && ast_is_command(node->left)
			&& node->right && ast_is_command(node->right));
	return (0);
}
