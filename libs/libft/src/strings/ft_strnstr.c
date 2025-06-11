/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 21:47:31 by sabruma           #+#    #+#             */
/*   Updated: 2024/11/21 21:47:37 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
static void	*ft_memmem(const void *h, size_t hl, const void *n, size_t nl);

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	if (*needle == '\0')
		return ((char *)haystack);
	if (*haystack == '\0')
		return (NULL);
	return ((char *)ft_memmem(haystack, len, needle, ft_strlen(needle)));
}

static void	*ft_memmem(const void *h, size_t hl, const void *n, size_t nl)
{
	unsigned char	*c_haystack;

	c_haystack = (unsigned char *)h;
	while (hl >= nl)
	{
		if (ft_memcmp(c_haystack, n, nl) == 0)
			return ((void *)c_haystack);
		c_haystack++;
		hl--;
	}
	return (NULL);
}
