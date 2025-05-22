#include "ast.h"

static t_ast	**f_base(t_ast *r, int (*p)(const t_ast *), size_t *d, int n);

// Core filter: returns array of the nodes matching predicate.
// Count is the number of matches
t_ast **ast_filter_n(t_ast *root, int (*predicate)(const t_ast *), size_t *dim)
{
	return (f_base(root, predicate, dim, 0));
}

// Same as _n version but the array is NULL-terminated
// Doesn't support NULL elements
t_ast **ast_filter(t_ast *root, int (*predicate)(const t_ast *))
{
	return (f_base(root, predicate, NULL, 1));
}

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

static t_ast	**f_base(t_ast *r, int (*p)(const t_ast *), size_t *d, int n)
{
	t_list	*matches;
	t_ast	**result;
	size_t	len;

	ast_filter_lst(r, p, &matches);
	result = (t_ast **)lst_to_array_ex(matches, &len, n);
	ft_lstclear(&matches, free_ast_void);
	if (d)
		*d = len;
	return (result);
}

void ast_filter_lst(t_ast *node, int (*predicate)(const t_ast *), t_list **out)
{
	if (!node)
		return ;
	if (predicate(node))
		ft_lstadd_back(out, ft_lstnew(node));
	ast_filter_lst(node->left, predicate, out);
	ast_filter_lst(node->right, predicate, out);
}

//TODO: libft
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