/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtxdup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 20:19:04 by sabruma           #+#    #+#             */
/*   Updated: 2025/06/21 20:31:19 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

// NULL-terminated matrix only
void	**mtxdup(void **mtx, void *(c)(void *), void(*f)(void *))
{
	size_t	dim;

	if (!mtx)
		return (NULL);
	dim = mtx_count(mtx);
	return (mtxdup_n(mtx, dim, c, f));
}
