#include "ast.h"

t_ast **ast_lst_to_array_n(t_list *lst, size_t *dim)
{
	return ((t_ast **)lst_to_array_n(lst, dim));
}
