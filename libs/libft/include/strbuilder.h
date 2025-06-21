/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strbuilder.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 21:47:19 by sabruma           #+#    #+#             */
/*   Updated: 2025/06/21 21:47:20 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRBUILDER_H
# define STRBUILDER_H

# include <stdlib.h>
# include "memory.h"
# include "strings.h"

# define GROWTH_FACTOR 2

typedef struct s_strbuilder
{
	char	*buf;	// Internal buffer
	size_t	len;	// Current length of the string
	size_t	cap;	// Allocated buffer size
}	t_sb;

int		sb_ensure_capacity(t_sb *sb, size_t required);
void	sb_append_char(t_sb *sb, char c);
void	sb_append_n(t_sb *sb, const char *data, size_t n);
void	sb_append_str(t_sb *sb, const char *str);
void	sb_clear(t_sb *sb);
void	sb_free(t_sb *sb);
void	sb_shrink_to_fit(t_sb *sb);
size_t	sb_capacity(t_sb *sb);
size_t	sb_length(t_sb *sb);
char	*sb_build(t_sb *sb);
t_sb	*sb_create(size_t initial_capacity);

#endif
