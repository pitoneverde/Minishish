/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 21:04:43 by sabruma           #+#    #+#             */
/*   Updated: 2024/12/06 21:04:47 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstadd_front(t_list **list, t_list *new);

t_list	*ft_lstadd_front(t_list **list, t_list *new)
{
	new->next = *list;
	*list = new;
	return (new);
}
