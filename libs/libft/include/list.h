/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 20:22:20 by sabruma           #+#    #+#             */
/*   Updated: 2025/06/21 20:22:22 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(LIST_H)
# define LIST_H
# include <stdlib.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

int		ft_lstsize(t_list *lst);
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list	*ft_lstnew(void *content);
t_list	*ft_lstadd_front(t_list **list, t_list *new);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstadd_back(t_list **list, t_list *new);
void	**lst_to_array(t_list *lst);
void	**lst_to_array_n(t_list *lst, size_t *dim);
void	**lst_to_array_ex(t_list *lst, size_t *dim, int nul);

#endif // LIST_H
