/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 22:46:01 by sabruma           #+#    #+#             */
/*   Updated: 2024/11/29 22:46:02 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2);

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*m;

	m = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!m)
		return (NULL);
	ft_strlcpy(m, s1, ft_strlen(s1) + 1);
	ft_strlcat(m, s2, ft_strlen(s1) + ft_strlen(s2) + 1);
	return (m);
}
