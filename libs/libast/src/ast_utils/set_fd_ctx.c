/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_fd_ctx.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 18:23:50 by plichota          #+#    #+#             */
/*   Updated: 2025/07/09 15:59:35 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

void	set_fd_ctx(t_fctx *ctx, int fd, t_ast_type type)
{
	if (type == AST_REDIR_IN || type == AST_HEREDOC)
	{
		if (ctx->fd_in != STDIN_FILENO)
			close(ctx->fd_in);
		ctx->fd_in = fd;
	}
	else if (type == AST_APPEND || type == AST_REDIR_OUT)
	{
		if (ctx->fd_out != STDOUT_FILENO)
			close(ctx->fd_out);
		ctx->fd_out = fd;
	}
	else
		perror("Wrong type (fd_ctx)");
}
