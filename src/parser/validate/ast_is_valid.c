/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_is_valid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 22:50:13 by sabruma           #+#    #+#             */
/*   Updated: 2025/07/14 21:15:56 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	ast_cmd_is_valid(t_ast *node);
static int	ast_literal_is_valid(t_ast *node);
static int	ast_pipe_is_valid(t_ast *node);
static int	ast_redir_is_valid(t_ast *node);

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

// SYNTAX CHECK
int	ast_is_valid(t_ast *node)
{
	if (!node)
		return (1);
	if (ast_has_error(node))
		return (0);
	if (node->type == AST_COMMAND)
		return (ast_cmd_is_valid(node));
	else if (node->type == AST_LITERAL)
		return (ast_literal_is_valid(node));
	else if (node->type == AST_PIPE)
		return (ast_pipe_is_valid(node));
	else if (ast_is_redirection(node))
		return (ast_redir_is_valid(node));
	node->error = ft_strdup("newline");
	return (0);
}

// if (!node->left && !ast_is_valid(node->left))
// 	return (0);
static int	ast_redir_is_valid(t_ast *node)
{
	if (!node->right)
	{
		node->error = ft_strdup(node->value);
		return (0);
	}
	if (node->right->type != AST_LITERAL || !node->right->value)
	{
		node->error = ft_strdup(node->value);
		return (0);
	}
	if (node->left && !ast_is_valid(node->left))
	{
		node->error = ft_strdup("newline");
		return (0);
	}
	return (1);
}

static int	ast_pipe_is_valid(t_ast *node)
{
	if (!node->left)
	{
		node->error = ft_strdup("|");
		return (0);
	}
	if (!node->right)
	{
		node->error = ft_strdup("newline");
		return (0);
	}
	if (!ast_is_valid(node->left) || !ast_is_valid(node->right))
		return (0);
	return (1);
}

static int	ast_literal_is_valid(t_ast *node)
{
	if (!node->value)
	{
		node->error = ft_strdup("newline");
		return (0);
	}
	return (1);
}

static int	ast_cmd_is_valid(t_ast *node)
{
	if (!node->argv || !node->argv[0])
	{
		node->error = ft_strdup("newline");
		return (0);
	}
	return (1);
}
