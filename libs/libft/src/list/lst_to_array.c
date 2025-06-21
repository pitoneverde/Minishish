/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_to_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 20:17:04 by sabruma           #+#    #+#             */
/*   Updated: 2025/06/21 20:18:23 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	**lst_to_array(t_list *lst);

// NULL-terminated
void	**lst_to_array(t_list *lst)
{
	size_t	dummy;

	return (lst_to_array_ex(lst, &dummy, 1));
}
