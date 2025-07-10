/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_ast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:28:48 by sabruma           #+#    #+#             */
/*   Updated: 2025/07/10 17:02:49 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_ast	*validate_ast_node(t_ast *node);

void	validate_ast(t_ast **root)
{
	if (!root)
		return ;
	astt_post_rpl(root, validate_ast_node);
	// if (*root && (*root)->type == AST_ERROR)
	// 	fprintf(stderr, "❌ Parse error: %s\n", (*root)->error);
}

static t_ast	*validate_ast_node(t_ast *node)
{
	char	*msg;

	if (!node || ast_has_error(node))
		return (node);
	if (node->left)
		node->left = validate_ast_node(node->left);
	if (node->right)
		node->right = validate_ast_node(node->right);
	if (!ast_is_valid(node))
	{
		if (node->error)
			msg = node->error;
		else
			msg = "syntax error near unexpected token `newline`";
		return (syntax_error_token((char *)msg));
	}
	return (node);
}

// Returns the error message string from the first AST_ERROR node found in the tree.
// Searches current node, then left subtree, then right subtree.
// Returns NULL if no error node is found.
const char *ast_get_error(const t_ast *node)
{
	const char *err;

	if (!node)
		return NULL;

	if (node->type == AST_ERROR && node->error)
		return node->error;

	err = ast_get_error(node->left);
	if (err)
		return err;

	err = ast_get_error(node->right);
	if (err)
		return err;

	return NULL;
}
