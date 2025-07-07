/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_ctx_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 18:20:19 by plichota          #+#    #+#             */
/*   Updated: 2025/07/07 18:20:37 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

void	fd_ctx_free(t_fd_ctx *ctx)
{
	if (!ctx)
		return ;
	if (ctx->fd_in != STDIN_FILENO && ctx->fd_in >= 0)
		close(ctx->fd_in);
	if (ctx->fd_out != STDOUT_FILENO && ctx->fd_out >= 0)
		close(ctx->fd_out);
	free(ctx);
}
