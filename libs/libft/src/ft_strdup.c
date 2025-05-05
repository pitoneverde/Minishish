/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 22:44:47 by sabruma           #+#    #+#             */
/*   Updated: 2024/11/29 22:44:48 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s);

char	*ft_strdup(const char *s)
{
	char	*c;

	c = (char *)malloc(ft_strlen(s) + 1);
	if (!c)
		return (NULL);
	ft_strlcpy(c, s, ft_strlen(s) + 1);
	return (c);
}
