/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_is_operator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 22:37:23 by sabruma           #+#    #+#             */
/*   Updated: 2025/06/21 22:37:24 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

int	ast_is_operator(const t_ast *node)
{
	return (node && (node->type == AST_APPEND || node->type == AST_HEREDOC
			|| node->type == AST_PIPE || node->type == AST_REDIR_IN
			|| node->type == AST_REDIR_OUT));
}
