/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_binary_op.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 22:31:19 by sabruma           #+#    #+#             */
/*   Updated: 2025/06/21 22:31:51 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

// create binary operator node (pipe or redirection)
t_ast	*ast_binary_op(t_ast_type type, char *op, t_ast *left, t_ast *right)
{
	t_ast	*opnode;

	opnode = ast_new(type, op);
	if (!opnode)
		return (ast_free(left), ast_free(right), NULL);
	opnode->left = left;
	opnode->right = right;
	return (opnode);
}
