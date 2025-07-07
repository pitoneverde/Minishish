/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_fd_ctx.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 18:23:50 by plichota          #+#    #+#             */
/*   Updated: 2025/07/07 18:24:46 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

void	set_fd_ctx(t_fd_ctx *ctx, int fd, t_ast_type type)
{
	if (type == AST_REDIR_IN || type == AST_HEREDOC)
	{
		if (ctx->fd_in != STDIN_FILENO)
			close(ctx->fd_in);
		ctx->fd_in = fd;
	}
	else
	{
		if (ctx->fd_out != STDOUT_FILENO)
			close(ctx->fd_out);
		ctx->fd_out = fd;
	}
}
