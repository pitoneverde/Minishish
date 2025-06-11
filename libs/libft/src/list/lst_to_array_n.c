#include "libft.h"

// not NULL-terminated
void **lst_to_array_n(t_list *lst, size_t *dim);

void **lst_to_array_n(t_list *lst, size_t *dim)
{
	return (lst_to_array_ex(lst, dim, 0));
}
