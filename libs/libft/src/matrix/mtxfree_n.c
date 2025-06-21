/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtxfree_n.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 20:19:22 by sabruma           #+#    #+#             */
/*   Updated: 2025/06/21 20:19:46 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

// frees a matrix of any type (given dim)
// 'f' is to free one row
void	mtxfree_n(void **matrix, size_t dim, void (*f)(void *))
{
	size_t	i;

	if (!matrix || !f)
		return ;
	i = 0;
	while (i < dim && matrix[i])
		f(matrix[i++]);
	free(matrix);
	matrix = NULL;
}
