/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtx_count.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 20:20:22 by sabruma           #+#    #+#             */
/*   Updated: 2025/06/21 20:20:29 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

// NULL-terminated matrix only
size_t	mtx_count(void **matrix)
{
	size_t	n;

	n = 0;
	while (matrix && matrix[n])
		n++;
	return (n);
}
