/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astdup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 22:28:50 by sabruma           #+#    #+#             */
/*   Updated: 2025/07/07 17:12:51 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

static void	*astdup_void(void *ast);

t_ast	*astdup(const t_ast *node)
{
	t_ast	*clone;

	if (!node)
		return (NULL);
	if (node->value)
		clone = ast_new(node->type, node->value);
	else
		clone = ast_new(node->type, NULL);
	if (node->argv)
		clone->argv = mtxdup_str(node->argv);
	if (node->error)
		clone->error = ft_strdup(node->error);
	if (node->quote)
		clone->quote = node->quote;
	if (node->args)
		clone->args = ft_lstmap(node->args, astdup_void, ast_free_void);
	if (node->fd_ctx)
		clone->fd_ctx = ft_structdup(node->fd_ctx);
	clone->argc = node->argc;
	clone->left = astdup(node->left);
	clone->right = astdup(node->right);
	return (clone);
}

static void	*astdup_void(void *ast)
{
	return (astdup((t_ast *)ast));
}
