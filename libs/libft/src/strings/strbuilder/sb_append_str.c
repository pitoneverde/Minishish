/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sb_append_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 20:14:12 by sabruma           #+#    #+#             */
/*   Updated: 2025/06/21 20:14:16 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "strbuilder.h"

// Appends a null-terminated string to the builder.
void	sb_append_str(t_sb *sb, const char *str)
{
	if (!str)
		return ;
	sb_append_n(sb, str, ft_strlen(str));
}
