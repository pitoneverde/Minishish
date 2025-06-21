/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_is_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 22:37:40 by sabruma           #+#    #+#             */
/*   Updated: 2025/06/21 22:37:41 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

int	ast_is_command(const t_ast *node)
{
	printf("is command %d\n", node && node->type == AST_COMMAND);
	return (node && node->type == AST_COMMAND);
}
