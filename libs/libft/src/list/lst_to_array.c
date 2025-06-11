#include "libft.h"

void **lst_to_array(t_list *lst);

// NULL-terminated
void **lst_to_array(t_list *lst)
{
	size_t dummy;
	return (lst_to_array_ex(lst, &dummy, 1));
}
