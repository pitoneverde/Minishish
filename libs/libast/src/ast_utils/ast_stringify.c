/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_stringify.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 22:49:00 by sabruma           #+#    #+#             */
/*   Updated: 2025/06/21 22:49:00 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

static void	ast_cmd_to_string(t_ast *node);
static void	ast_redir_to_string(t_ast *node);
static void	ast_pipe_to_string(t_ast *node);
static void	ast_error_to_string(t_ast *node);

// uses bottom-up approch for recursion (first processes leaves)
void	ast_stringify(t_ast *node)
{
	if (!node)
		return ;
	ast_stringify(node->left);
	ast_stringify(node->right);
	if (node->type == AST_COMMAND)
		ast_cmd_to_string(node);
	else if (node->type == AST_REDIR_IN || node->type == AST_REDIR_OUT
		|| node->type == AST_APPEND || node->type == AST_HEREDOC)
		ast_redir_to_string(node);
	else if (node->type == AST_PIPE)
		ast_pipe_to_string(node);
	else if (node->type == AST_ERROR)
		ast_error_to_string(node);
}

// +1 for space between args
static void	ast_cmd_to_string(t_ast *node)
{
	size_t	len;
	char	*new_val;
	int		i;

	if (!node || node->type != AST_COMMAND || !node->argv)
		return ;
	len = 0;
	i = 0;
	while (node->argv[i])
		len += ft_strlen(node->argv[i++]) + 1;
	new_val = (char *)malloc(len + 1);
	if (!new_val)
		return ;
	new_val[0] = '\0';
	i = 0;
	while (node->argv[i])
	{
		ft_strlcat(new_val, node->argv[i], len + 1);
		if (node->argv[i + 1])
			ft_strlcat(new_val, " ", len + 1);
		i++;
	}
	free(node->value);
	node->value = new_val;
}

static void	ast_redir_to_string(t_ast *node)
{
	char	*new_val;
	size_t	len;

	if (!node || !node->left || !node->right
		|| !node->right->value || !node->left->value)
		return ;
	if (!node->right || !node->right->value)
		return ;
	len = ft_strlen(node->left->value)
		+ ft_strlen(node->value)
		+ ft_strlen(node->right->value) + 3;
	new_val = (char *)malloc(len + 1);
	if (!new_val)
		return ;
	new_val[0] = '\0';
	ft_strlcat(new_val, node->left->value, len + 1);
	ft_strlcat(new_val, " ", len + 1);
	ft_strlcat(new_val, node->value, len + 1);
	ft_strlcat(new_val, " ", len + 1);
	ft_strlcat(new_val, node->right->value, len + 1);
	free(node->value);
	node->value = new_val;
}

// +3 cause " | "
static void	ast_pipe_to_string(t_ast *node)
{
	size_t	len;
	char	*new_val;

	if (!node || node->type != AST_PIPE || !node->left || !node->right)
		return ;
	if (!node->left->value || !node->right->value)
		return ;
	len = ft_strlen(node->left->value) + ft_strlen(node->right->value) + 3;
	new_val = (char *)malloc(len + 1);
	if (!new_val)
		return ;
	new_val[0] = '\0';
	ft_strlcat(new_val, node->left->value, len + 1);
	ft_strlcat(new_val, " ", len + 1);
	ft_strlcat(new_val, "|", len + 1);
	ft_strlcat(new_val, " ", len + 1);
	ft_strlcat(new_val, node->right->value, len + 1);
	free(node->value);
	node->value = new_val;
}

static void	ast_error_to_string(t_ast *node)
{
	if (!node || node->type != AST_ERROR || !node->error)
		return ;
	free(node->value);
	node->value = ft_strdup(node->error);
}
