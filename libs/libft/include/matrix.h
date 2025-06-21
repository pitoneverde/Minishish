/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 20:22:25 by sabruma           #+#    #+#             */
/*   Updated: 2025/06/21 20:33:43 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

# include <stdlib.h>
# include "strings.h"

// Core low-level matrix utilities
size_t	mtx_count(void **matrix);
void	mtxfree(void **mtx, void (*f)(void *));
void	mtxfree_n(void **mtx, size_t dim, void (*f)(void *));
void	**mtxdup(void **mtx, void *(c)(void *), void(*f)(void *));
void	**mtxdup_n(void **mtx, size_t dim, void *(c)(void *), void(f)(void *));

// wrappers for project specific matrix handling
void	print_string_matrix(char **matrix);

static inline char	**mtxdup_str(char **matrix)
{
	return ((char **)mtxdup((void **)matrix, ft_strdup, free));
}

static inline void	mtxfree_str(char **matrix)
{
	mtxfree((void **)matrix, free);
}

#endif // !MATRIX_HELPERS_H