/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 22:45:25 by sabruma           #+#    #+#             */
/*   Updated: 2024/11/29 22:45:26 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *block, int c, size_t size);

void	*ft_memset(void *block, int c, size_t size)
{
	void	*saveblock;

	if (!block)
		return (NULL);
	saveblock = block;
	while (size--)
		*(unsigned char *)block++ = (unsigned char)c;
	return (saveblock);
}
