/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sb_length.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 20:13:41 by sabruma           #+#    #+#             */
/*   Updated: 2025/06/21 20:13:46 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "strbuilder.h"

// Returns the current length of the string.
size_t	sb_length(t_sb *sb)
{
	return (sb->len);
}
