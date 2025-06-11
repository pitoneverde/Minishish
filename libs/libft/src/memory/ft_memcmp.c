/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 22:43:04 by sabruma           #+#    #+#             */
/*   Updated: 2024/11/29 22:43:09 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *a1, const void *a2, size_t size);

int	ft_memcmp(const void *a1, const void *a2, size_t size)
{
	unsigned char	c1;
	unsigned char	c2;
	size_t			i;

	i = 0;
	while (i++ < size)
	{
		c1 = *(unsigned char *)a1++;
		c2 = *(unsigned char *)a2++;
		if (c1 != c2)
			return ((int)c1 - c2);
	}
	return (0);
}
