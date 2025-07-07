/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 22:26:14 by sabruma           #+#    #+#             */
/*   Updated: 2025/07/07 18:26:35 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

void	ast_free(t_ast *tree)
{
	if (!tree)
		return ;
	ast_free(tree->left);
	ast_free(tree->right);
	if (tree->value)
		free(tree->value);
	if (tree->error)
		free(tree->error);
	if (tree->argv)
		mtxfree_str(tree->argv);
	if (tree->args)
		ft_lstclear(&tree->args, ast_free_void);
	if (tree->fd_ctx)
		fd_ctx_free(tree->fd_ctx);
	free(tree);
}
