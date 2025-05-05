/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 22:54:54 by sabruma           #+#    #+#             */
/*   Updated: 2024/11/29 22:54:56 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *to, const char *from, size_t size);

size_t	ft_strlcpy(char *to, const char *from, size_t size)
{
	if (size > 0 && size <= ft_strlen(from))
	{
		ft_memcpy(to, from, size - 1);
		to[size - 1] = '\0';
	}
	else if (size > ft_strlen(from))
	{
		ft_memcpy(to, from, ft_strlen(from));
		to[ft_strlen(from)] = '\0';
	}
	return (ft_strlen(from));
}
