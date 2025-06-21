/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_replace_subtree.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 22:46:12 by sabruma           #+#    #+#             */
/*   Updated: 2025/06/21 22:46:23 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

// assuming both are trees (and therefore malloc'ed)
void	ast_replace_subtree(t_ast **target, t_ast *replace)
{
	if (!target || *target == replace)
		return ;
	ast_free(*target);
	*target = replace;
}
