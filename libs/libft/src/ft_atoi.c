/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 21:38:39 by sabruma           #+#    #+#             */
/*   Updated: 2024/11/21 21:38:44 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_atoi(const char *str);
static int	ft_isspace(int c);

int	ft_atoi(const char *str)
{
	int	segno;
	int	numero;

	segno = 1;
	numero = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
		{
			segno *= -1;
		}
		str++;
	}
	while (ft_isdigit(*str))
	{
		numero *= 10;
		numero += *str - '0';
		str++;
	}
	return (numero * segno);
}

static int	ft_isspace(int c)
{
	if ((c >= 0x09 && c <= 0x0D) || c == 0x20)
		return (c);
	return (0);
}
