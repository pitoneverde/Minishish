/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 22:44:17 by sabruma           #+#    #+#             */
/*   Updated: 2024/11/29 22:44:20 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *block, int c, size_t size);

void	*ft_memchr(const void *block, int c, size_t size)
{
	size_t			i;
	unsigned char	*c_block;

	c_block = (unsigned char *)block;
	i = 0;
	while (i < size)
	{
		if (*c_block == (unsigned char)c)
			return (c_block);
		c_block++;
		i++;
	}
	return (NULL);
}
