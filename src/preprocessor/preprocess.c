/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preprocess.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 17:33:59 by plichota          #+#    #+#             */
/*   Updated: 2025/07/13 19:39:36 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// dispatches the redirection handler based on the node type
// returns the fd of the opened file, -1 if any error occured
int	get_redir_fd(t_ast *redir, t_sh *shell)
{
	if (redir->type == AST_REDIR_IN)
		return (handle_redir_in(redir, shell));
	if (redir->type == AST_REDIR_OUT)
		return (handle_redir_out(redir, shell));
	if (redir->type == AST_APPEND)
		return (handle_append(redir, shell));
	if (redir->type == AST_HEREDOC)
		return (handle_heredoc(redir, shell));
	perror("Unknown redirection");
	return (-1);
}

// recursively searches for the nearest command in the left subtree
// returns the node command, NULL if not found
t_ast	*get_command_node(t_ast *node)
{
	if (!node)
		return (NULL);
	if (ast_is_command(node))
		return (node);
	return (get_command_node(node->left));
}

// applies the redirection, creates a ctx in the node 
// returns 0 on success, -1 if any error occured,
// EXIT_HEREDOC_SIGINT if Ctrl-C is pressed
int	apply_redirection(t_ast *ast, t_sh *shell)
{
	t_ast		*cmd;
	t_fctx		*ctx;
	int			fd;

	if (!ast || !ast->left)
		return (-1);
	cmd = get_command_node(ast->left);
	if (!cmd)
		return (-1);
	if (!cmd->fd_ctx)
	{
		cmd->fd_ctx = fd_ctx_new();
		if (!cmd->fd_ctx)
			return (perror("malloc fd_ctx_new"), -1);
	}
	ctx = cmd->fd_ctx;
	fd = get_redir_fd(ast, shell);
	if (fd == EXIT_HEREDOC_SIGINT)
		return (EXIT_HEREDOC_SIGINT);
	if (fd < 0)
		return (-1);
	set_fd_ctx(ctx, fd, ast->type);
	return (0);
}

// recursively applies all redirections
// returns 0 on success, -1 if any error occured
int	process_ast_redirections(t_ast *ast, t_sh *shell)
{
	if (!ast)
		return (0);
	if (process_ast_redirections(ast->left, shell) != 0)
		return (-1);
	if (process_ast_redirections(ast->right, shell) != 0)
		return (-1);
	if (ast_is_redirection(ast))
		return (apply_redirection(ast, shell));
	return (0);
}
