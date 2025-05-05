/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 22:56:20 by sabruma           #+#    #+#             */
/*   Updated: 2024/11/29 22:56:22 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_isprint(int c);
static int	ft_ispunct(int c);

int	ft_isprint(int c)
{
	return (ft_isalnum(c) || c == 0x20 || ft_ispunct(c));
}

static int	ft_ispunct(int c)
{
	if (c >= 0x21 && c <= 0x7E && !ft_isalnum(c))
		return (c);
	return (0);
}
