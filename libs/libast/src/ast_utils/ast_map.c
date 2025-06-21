/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 22:46:00 by sabruma           #+#    #+#             */
/*   Updated: 2025/06/21 22:46:06 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

// behaves like foreach
void	ast_map(t_ast *node, void (*f)(t_ast *))
{
	if (!node || !f)
		return ;
	f(node);
	ast_map(node->left, f);
	ast_map(node->right, f);
}
