/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astdup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 22:28:50 by sabruma           #+#    #+#             */
/*   Updated: 2025/07/14 18:17:06 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

static void	*astdup_void(void *ast);

// NOTE: check for malloc fails
t_ast	*astdup(const t_ast *node)
{
	t_ast	*clone;

	if (!node)
		return (NULL);
	clone = ast_new(node->type, node->value);
	if (!clone)
		return (NULL);
	if (node->argv)
		clone->argv = mtxdup_str(node->argv);
	if (node->args)
		clone->args = ft_lstmap(node->args, astdup_void, ast_free_void);
	if (node->fd_ctx)
		clone->fd_ctx = ft_fctxdup(node->fd_ctx);
	clone->error = node->error;
	clone->quote = node->quote;
	clone->argc = node->argc;
	clone->left = astdup(node->left);
	clone->right = astdup(node->right);
	return (clone);
}

static void	*astdup_void(void *ast)
{
	return (astdup((t_ast *)ast));
}
