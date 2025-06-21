/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_to_array_ex.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 20:17:30 by sabruma           #+#    #+#             */
/*   Updated: 2025/06/21 20:17:53 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	**lst_to_array_ex(t_list *lst, size_t *dim, int nul);

// base version
void	**lst_to_array_ex(t_list *lst, size_t *dim, int nul)
{
	size_t	i;
	void	**arr;

	*dim = ft_lstsize(lst);
	arr = malloc((*dim + nul) * sizeof(void *));
	if (!arr)
		return (NULL);
	i = 0;
	while (lst)
	{
		arr[i++] = lst->content;
		lst = lst->next;
	}
	if (nul)
		arr[i] = NULL;
	return (arr);
}
