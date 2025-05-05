/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 22:56:35 by sabruma           #+#    #+#             */
/*   Updated: 2024/11/29 22:56:36 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_itoa(int n);
static int	get_len(int n);

char	*ft_itoa(int n)
{
	char	*s;
	int		sign;
	int		len;

	if (n == INT_MIN)
		return (ft_strdup("-2147483648"));
	sign = 1;
	len = get_len(n);
	s = (char *)ft_calloc(len + 1, 1);
	if (!s)
		return (NULL);
	if (n < 0)
	{
		n = -n;
		sign = -1;
	}
	while (len > 0)
	{
		s[--len] = n % 10 + '0';
		n /= 10;
	}
	if (sign == -1)
		s[0] = '-';
	return (s);
}

static int	get_len(int n)
{
	int	len;
	int	sign;

	sign = 1;
	len = 1;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n = -n;
		sign = -1;
	}
	while (n > 0)
	{
		len++;
		n /= 10;
	}
	if (sign == -1)
		return (len);
	return (len - 1);
}
