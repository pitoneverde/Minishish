/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ispunct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 20:11:12 by sabruma           #+#    #+#             */
/*   Updated: 2025/06/21 20:11:17 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "chars.h"

int	ft_ispunct(int c);

int	ft_ispunct(int c)
{
	if (c >= 0x21 && c <= 0x7E && !ft_isalnum(c))
		return (c);
	return (0);
}
