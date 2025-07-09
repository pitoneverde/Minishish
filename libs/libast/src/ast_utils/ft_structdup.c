/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_structdup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 17:09:09 by plichota          #+#    #+#             */
/*   Updated: 2025/07/09 15:59:35 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

t_fctx	*ft_structdup(const t_fctx *fd_ctx)
{
	t_fctx	*copy;

	if (!fd_ctx)
		return (NULL);
	copy = malloc(sizeof(t_fctx));
	if (!copy)
		return (NULL);
	copy->fd_in = fd_ctx->fd_in;
	copy->fd_out = fd_ctx->fd_out;
	return (copy);
}
