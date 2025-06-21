/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sb_append_n.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 20:13:53 by sabruma           #+#    #+#             */
/*   Updated: 2025/06/21 20:14:02 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "strbuilder.h"

// Appends `n` bytes from a buffer (not necessarily null-terminated).
void	sb_append_n(t_sb *sb, const char *data, size_t n)
{
	if (!sb_ensure_capacity(sb, sb->len + n))
		return ;
	ft_memcpy(sb->buf + sb->len, data, n);
	sb->len += n;
}
