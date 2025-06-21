/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_string.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 22:06:15 by sabruma           #+#    #+#             */
/*   Updated: 2025/06/21 22:12:20 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "strings.h"

// adapter for libft/matrix.h
void	*copy_string(void *str)
{
	return (ft_strdup((char *)str));
}
