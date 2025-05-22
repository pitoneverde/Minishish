#include "ast.h"

t_ast **ast_lst_to_array(t_list *lst)
{
	return ((t_ast **)lst_to_array(lst));
}

t_ast **ast_lst_to_array_n(t_list *lst, size_t *dim)
{
	return ((t_ast **)lst_to_array_n(lst, dim));
}

// NULL-terminated
void **lst_to_array(t_list *lst)
{
	size_t dummy;
	return (lst_to_array_ex(lst, &dummy, 1));
}

// not NULL-terminated
void **lst_to_array_n(t_list *lst, size_t *dim)
{
	return (lst_to_array_ex(lst, dim, 0));
}

// TODO: libft
void **lst_to_array_ex(t_list *lst, size_t *dim, int nul)
{
	size_t i;
	void **arr;

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