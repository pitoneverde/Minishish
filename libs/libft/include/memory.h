/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 20:22:06 by sabruma           #+#    #+#             */
/*   Updated: 2025/06/21 20:22:07 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(MEMORY_H)
# define MEMORY_H
# include <stdlib.h>

int		ft_memcmp(const void *a1, const void *a2, size_t size);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nitems, size_t size);
void	*ft_memset(void *block, int c, size_t size);
void	*ft_memchr(const void *block, int c, size_t size);
void	*ft_memcpy(void *to, const void *from, size_t size);
void	*ft_memmove(void *to, const void *from, size_t size);
void	*ft_realloc(void *old_ptr, size_t old_size, size_t new_size);

#endif // MEMORY_H
