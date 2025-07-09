/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_ctx_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 17:18:06 by plichota          #+#    #+#             */
/*   Updated: 2025/07/09 15:59:35 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

t_fctx	*fd_ctx_new(void)
{
	t_fctx	*ctx;

	printf("new context\n");
	ctx = malloc(sizeof(t_fctx));
	if (!ctx)
		return (NULL);
	ctx->fd_in = STDIN_FILENO;
	ctx->fd_out = STDOUT_FILENO;
	return (ctx);
}
