/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:02:10 by plichota          #+#    #+#             */
/*   Updated: 2025/06/21 20:25:38 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 256
# endif

# include <unistd.h>
# include <stddef.h>
# include <limits.h>

# include "chars.h"
# include "memory.h"
# include "output.h"
# include "strings.h"
# include "matrix.h"
# include "strbuilder.h"

// Bonus
# include "list.h"

// conversion
int		ft_atoi(const char *str);
char	*ft_itoa(int n);

// Get Next Line
char	*get_next_line(int fd);

#endif