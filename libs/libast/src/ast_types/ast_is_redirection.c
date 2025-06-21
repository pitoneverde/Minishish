/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_is_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 22:44:33 by sabruma           #+#    #+#             */
/*   Updated: 2025/06/21 22:44:43 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

int	ast_is_redirection(const t_ast *node)
{
	return (node->type == AST_REDIR_IN || node->type == AST_REDIR_OUT
		|| node->type == AST_HEREDOC || node->type == AST_APPEND);
}
