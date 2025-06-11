/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 22:46:15 by sabruma           #+#    #+#             */
/*   Updated: 2024/11/29 22:46:17 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *to, const void *from, size_t size);

void	*ft_memcpy(void *to, const void *from, size_t size)
{
	void	*saveto;

	if (to == NULL && from == NULL)
		return (NULL);
	saveto = to;
	while (size--)
		*(unsigned char *)to++ = *(unsigned char *)from++;
	return (saveto);
}
