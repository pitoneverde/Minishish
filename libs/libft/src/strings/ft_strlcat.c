/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 21:46:49 by sabruma           #+#    #+#             */
/*   Updated: 2024/11/21 21:47:02 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *to, const char *from, size_t size);

size_t	ft_strlcat(char *to, const char *from, size_t size)
{
	size_t	len;
	size_t	i;

	i = 0;
	while (*to && i < size)
	{
		to++;
		i++;
	}
	len = ft_strlcpy(to, from, size - i);
	return (len + i);
}
