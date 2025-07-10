/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_is_valid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 22:50:13 by sabruma           #+#    #+#             */
/*   Updated: 2025/07/10 14:51:34 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

// SYNTAX CHECK
// int	ast_is_valid(const t_ast *node)
// {
// 	if (!node || ast_has_error(node))
// 		return (0);
// 	if (node->type == AST_COMMAND)
// 		return (node->argv != NULL && node->argv[0] != NULL);
// 	else if (node->type == AST_LITERAL)
// 		return (node->value != NULL);
// 	else if (node->type == AST_PIPE)
// 		return (node->left && node->right
// 			&& ast_is_valid(node->left)
// 			&& ast_is_valid(node->right));
// 	else if (ast_is_redirection(node))
// 		return (node->left && node->right
// 			&& ast_is_valid(node->left)
// 			&& node->right->type == AST_LITERAL
// 			&& ast_is_valid(node->right));
// 	else
// 		return (0);
// }

int ast_is_valid(const t_ast *node)
{
	if (!node || ast_has_error(node))
		return (0);

	if (node->type == AST_COMMAND)
	{
		// Must have argv[0] (command name), already set during expansion
		return (node->argv && node->argv[0]);
	}
	else if (node->type == AST_LITERAL)
	{
		// A literal must have a non-null value
		return (node->value != NULL);
	}
	else if (node->type == AST_PIPE)
	{
		// Pipe must have left and right children
		if (!node->left || !node->right)
			return (0);
		// // Left and right must not be redirections (e.g., `> file | cmd`)
		// if (ast_is_redirection(node->left) || ast_is_redirection(node->right))
		// 	return (0);
		// Recurse
		return (ast_is_valid(node->left) && ast_is_valid(node->right));
	}
	else if (ast_is_redirection(node))
	{
		// Redirection must have both children
		if (!node->right)
			return (0);
		// Right child must be a literal (the filename)
		if (node->right->type != AST_LITERAL || !node->right->value)
			return (0);
		// Recurse on left
		if (node->left)
			return (ast_is_valid(node->left));
	}
	// Unknown node type
	return (0);
}
