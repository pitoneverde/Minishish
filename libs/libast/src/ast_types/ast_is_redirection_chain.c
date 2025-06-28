/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_is_redirection_chain.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 22:37:49 by sabruma           #+#    #+#             */
/*   Updated: 2025/06/28 04:05:44 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

// something like: "< file1 > file2 >> file3"
int	ast_is_redirection_chain(const t_ast *node)
{
	if (!node || !ast_is_redirection(node) || !node->left)
		return (0);
	if (ast_is_command(node->left))
		return (1);
	if (ast_is_redirection(node->left))
		return (ast_is_redirection_chain(node->left));
	return (0);
}
