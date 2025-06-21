/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_lst_to_array_n.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 22:35:09 by sabruma           #+#    #+#             */
/*   Updated: 2025/06/21 22:35:09 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

t_ast	**ast_lst_to_array_n(t_list *lst, size_t *dim)
{
	return ((t_ast **)lst_to_array_n(lst, dim));
}
