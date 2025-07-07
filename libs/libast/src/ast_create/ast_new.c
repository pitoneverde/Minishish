/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 22:33:15 by sabruma           #+#    #+#             */
/*   Updated: 2025/07/07 17:13:49 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

// create generic node
t_ast	*ast_new(t_ast_type type, char *value)
{
	t_ast	*node;

	node = (t_ast *)malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = type;
	node->quote = N_QUOTE;
	node->value = NULL;
	node->left = NULL;
	node->right = NULL;
	node->error = NULL;
	node->argc = 0;
	node->argv = NULL;
	node->args = NULL;
	node->fd_ctx = NULL;
	if (value)
		node->value = ft_strdup(value);
	return (node);
}
