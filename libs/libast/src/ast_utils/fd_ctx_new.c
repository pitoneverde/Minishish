/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_ctx_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 17:18:06 by plichota          #+#    #+#             */
/*   Updated: 2025/07/07 17:20:52 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

t_fd_ctx	*fd_ctx_new(void)
{
	t_fd_ctx	*ctx;

	ctx = malloc(sizeof(t_fd_ctx));
	if (!ctx)
		return (NULL);
	ctx->fd_in = STDIN_FILENO;
	ctx->fd_out = STDOUT_FILENO;
	return (ctx);
}
