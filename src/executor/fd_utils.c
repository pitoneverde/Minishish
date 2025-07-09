/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 23:13:51 by plichota          #+#    #+#             */
/*   Updated: 2025/07/09 15:30:09 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_std_fd(int fd_in, int fd_out)
{
	if (fd_in != STDIN_FILENO)
	{
		if (dup2(fd_in, STDIN_FILENO) == -1)
		{
			perror("dup2 fd_in failed");
			exit(1);
		}
		close(fd_in);
	}
	if (fd_out != STDOUT_FILENO)
	{
		if (dup2(fd_out, STDOUT_FILENO) == -1)
		{
			perror("dup2 fd_out failed");
			exit(1);
		}
		close(fd_out);
	}
}

void	override_fd_with_ctx(t_ast *ast, int *new_fd_in, int *new_fd_out)
{
	if (!ast || !ast->fd_ctx)
		return ;
	if (ast->fd_ctx->fd_in != STDIN_FILENO)
		*new_fd_in = ast->fd_ctx->fd_in;
	if (ast->fd_ctx->fd_out != STDOUT_FILENO)
		*new_fd_out = ast->fd_ctx->fd_out;
}
