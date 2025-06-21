/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 20:20:55 by sabruma           #+#    #+#             */
/*   Updated: 2025/06/21 20:21:09 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"

static size_t	min(size_t a, size_t b);

void	*ft_realloc(void *old_ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;
	size_t	i;
	size_t	copy_size;

	if (new_size == 0)
		return (free(old_ptr), NULL);
	if (new_size == old_size)
		return (old_ptr);
	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);
	if (old_ptr)
	{
		copy_size = min(old_size, new_size);
		i = 0;
		while (i < copy_size)
		{
			((unsigned char *)new_ptr)[i] = ((unsigned char *)old_ptr)[i];
			i++;
		}
		free(old_ptr);
	}
	return (new_ptr);
}

static size_t	min(size_t a, size_t b)
{
	if (a < b)
		return (a);
	return (b);
}
