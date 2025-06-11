/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 22:42:00 by sabruma           #+#    #+#             */
/*   Updated: 2024/11/29 22:42:03 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *string, int c);

char	*ft_strrchr(const char *string, int c)
{
	const char	*last;

	if ((char)c == '\0')
	{
		while (*string)
			string++;
		return ((char *)string);
	}
	last = NULL;
	while (*string)
	{
		if (*string == (char)c)
			last = string;
		string++;
	}
	return ((char *)last);
}
