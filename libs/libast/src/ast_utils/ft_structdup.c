/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_structdup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 17:09:09 by plichota          #+#    #+#             */
/*   Updated: 2025/07/07 17:20:16 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

t_fd_ctx	*ft_structdup(const t_fd_ctx *fd_ctx)
{
	t_fd_ctx	*copy;

	if (!fd_ctx)
		return (NULL);
	copy = malloc(sizeof(t_fd_ctx));
	if (!copy)
		return (NULL);
	copy->fd_in = fd_ctx->fd_in;
	copy->fd_out = fd_ctx->fd_out;
	return (copy);
}
