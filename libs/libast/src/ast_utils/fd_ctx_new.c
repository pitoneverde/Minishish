/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_ctx_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 17:18:06 by plichota          #+#    #+#             */
/*   Updated: 2025/07/09 18:52:19 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

t_fctx	*fd_ctx_new(void)
{
	t_fctx	*ctx;

	ctx = malloc(sizeof(t_fctx));
	if (!ctx)
		return (NULL);
	ctx->fd_in = STDIN_FILENO;
	ctx->fd_out = STDOUT_FILENO;
	return (ctx);
}
