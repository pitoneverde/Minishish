/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtxfree.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 20:19:53 by sabruma           #+#    #+#             */
/*   Updated: 2025/06/21 20:31:03 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

// NULL-terminated matrix only
void	mtxfree(void **mtx, void (*f)(void *))
{
	size_t	dim;

	if (!mtx)
		return ;
	dim = mtx_count(mtx);
	return (mtxfree_n(mtx, dim, f));
}
