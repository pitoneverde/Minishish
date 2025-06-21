/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtxdup_n.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 20:18:43 by sabruma           #+#    #+#             */
/*   Updated: 2025/06/21 20:18:52 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

// copies a matrix of any type (given dim)
// 'c' is to copy one row
// 'f' is to free one row
void	**mtxdup_n(void **mtx, size_t dim, void *(c)(void *), void(f)(void *))
{
	size_t	i;
	void	**copy;

	if (!mtx || !c)
		return (NULL);
	copy = malloc(sizeof(void *) * (dim + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < dim)
	{
		copy[i] = c(mtx[i]);
		if (!copy[i])
			return (mtxfree_n(copy, i, f), NULL);
		i++;
	}
	copy[dim] = NULL;
	return (copy);
}
