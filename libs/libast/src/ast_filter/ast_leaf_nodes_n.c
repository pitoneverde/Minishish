/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_leaf_nodes_n.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 22:23:33 by sabruma           #+#    #+#             */
/*   Updated: 2025/06/21 22:23:34 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

t_ast	**ast_leaf_nodes_n(t_ast *root, size_t *dim)
{
	return (ast_filter_n(root, ast_is_leaf, dim));
}
