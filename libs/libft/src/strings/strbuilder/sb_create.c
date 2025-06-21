/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sb_create.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 20:13:33 by sabruma           #+#    #+#             */
/*   Updated: 2025/06/21 20:13:34 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "strbuilder.h"

// Creates a new string builder with an initial capacity.
// `initial_capacity` must be > 0. Passing 0 results in undefined behavior.
t_sb	*sb_create(size_t initial_capacity)
{
	t_sb	*sb;

	sb = malloc(sizeof(t_sb));
	if (!sb)
		return (NULL);
	sb->buf = malloc(initial_capacity);
	if (!sb->buf)
		return (free(sb), NULL);
	sb->cap = initial_capacity;
	sb->len = 0;
	sb->buf[0] = '\0';
	return (sb);
}
