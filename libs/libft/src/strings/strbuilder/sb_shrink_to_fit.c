/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sb_shrink_to_fit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 20:12:58 by sabruma           #+#    #+#             */
/*   Updated: 2025/06/21 20:13:02 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "strbuilder.h"

// Shrinks the internal buffer to fit the current string exactly.
void	sb_shrink_to_fit(t_sb *sb)
{
	char	*new_buf;

	if (sb->len == sb->cap)
		return ;
	if (sb->len == 0)
	{
		free(sb->buf);
		sb->buf = NULL;
		sb->cap = 0;
	}
	new_buf = ft_realloc(sb->buf, sb->cap, sb->len);
	if (new_buf)
	{
		sb->buf = new_buf;
		sb->cap = sb->len;
	}
}
