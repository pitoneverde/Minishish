/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sb_append_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 20:12:16 by sabruma           #+#    #+#             */
/*   Updated: 2025/06/21 20:12:26 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "strbuilder.h"

// Appends a single character to the builder.
void	sb_append_char(t_sb *sb, char c)
{
	if (!sb_ensure_capacity(sb, sb->len + 1))
		return ;
	sb->buf[sb->len++] = c;
}
