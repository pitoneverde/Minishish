/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_flatten_post.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 22:34:06 by sabruma           #+#    #+#             */
/*   Updated: 2025/06/21 22:34:07 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

t_ast	**ast_flatten_post(t_ast *root, size_t *dim)
{
	t_list	*nodes;
	t_ast	**result;
	size_t	len;

	nodes = NULL;
	if (dim)
		*dim = 0;
	if (!root)
		return (NULL);
	astt_post_ctx(root, ast_flatten_visit, &nodes);
	result = ast_lst_to_array_n(nodes, &len);
	ft_lstclear(&nodes, NULL);
	if (dim)
		*dim = len;
	if (len == 0)
		return (free(result), NULL);
	return (result);
}
