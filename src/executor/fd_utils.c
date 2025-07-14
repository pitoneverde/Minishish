/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 23:13:51 by plichota          #+#    #+#             */
/*   Updated: 2025/07/13 22:28:37 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_std_fd(int fd_in, int fd_out)
{
	if (fd_in != STDIN_FILENO && fd_in != -1)
	{
		if (dup2(fd_in, STDIN_FILENO) == -1)
		{
			perror("dup2 fd_in failed");
			exit(1);
		}
		close(fd_in);
	}
	if (fd_out != STDOUT_FILENO && fd_out != -1)
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

void	close_unused_fds(t_ast *ast, int new_fd_in, int new_fd_out)
{
	t_fctx	*ctx;

	if (!ast || !ast->fd_ctx)
		return ;
	ctx = ast->fd_ctx;
	if (ctx->fd_in != STDIN_FILENO && ctx->fd_in != new_fd_in)
		close(ctx->fd_in);
	if (ctx->fd_out != STDOUT_FILENO && ctx->fd_out != new_fd_out)
		close(ctx->fd_out);
}
