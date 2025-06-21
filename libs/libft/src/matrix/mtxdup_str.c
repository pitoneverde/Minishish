/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtxdup_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 22:04:35 by sabruma           #+#    #+#             */
/*   Updated: 2025/06/21 22:12:59 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

char	**mtxdup_str(char **matrix)
{
	return ((char **)mtxdup((void **)matrix, copy_string, free));
}
