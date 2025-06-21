/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_to_array_n.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 20:17:59 by sabruma           #+#    #+#             */
/*   Updated: 2025/06/21 20:18:09 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// not NULL-terminated
void	**lst_to_array_n(t_list *lst, size_t *dim);

void	**lst_to_array_n(t_list *lst, size_t *dim)
{
	return (lst_to_array_ex(lst, dim, 0));
}
