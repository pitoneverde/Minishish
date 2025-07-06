/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 18:50:48 by plichota          #+#    #+#             */
/*   Updated: 2025/07/06 18:12:45 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// apre i file e imposta fd_in/fd_out (poi spawn_command e execute_command faranno il resto)
int execute_redirection_chain(t_ast *ast, t_sh *shell, int fd_in, int fd_out, int is_fork, int is_in_pipeline)
{
	int fd;

	if (!ast || !shell)
		return (127);

	if (ast->type == AST_REDIR_IN)
	{
		fd = handle_redir_in(ast, shell);
		if (fd == -1)
			return (1);
		return (executor(ast->left, fd, fd_out, shell, is_fork, is_in_pipeline));
	} else if (ast->type == AST_REDIR_OUT)
	{
		fd = handle_redir_out(ast, shell);
		if (fd == -1)
			return (1);
		return executor(ast->left, fd_in, fd, shell, is_fork, is_in_pipeline);
	} else if (ast->type == AST_APPEND)
	{
		fd = handle_append(ast, shell);
		if (fd == -1)
			return (1);
		return executor(ast->left, fd_in, fd, shell, is_fork, is_in_pipeline);
	} else if (ast->type == AST_HEREDOC)
	{
		fd = handle_heredoc(ast, shell);
		if (fd == -1)
			return (1);
		return executor(ast->left, fd, fd_out, shell, is_fork, is_in_pipeline);
	} else
		return (perror("Unknown redirection type"), 1); // to do ft_printf_fd

	return (0);
}