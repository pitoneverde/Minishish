/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sb_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 20:14:25 by sabruma           #+#    #+#             */
/*   Updated: 2025/06/21 20:15:12 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "strbuilder.h"

// Frees the builder and its buffer without returning a string.
void	sb_free(t_sb *sb)
{
	if (!sb)
		return ;
	if (sb->buf)
		free(sb->buf);
	free(sb);
}
