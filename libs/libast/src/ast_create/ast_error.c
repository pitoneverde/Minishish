/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 22:32:28 by sabruma           #+#    #+#             */
/*   Updated: 2025/06/21 22:32:45 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

t_ast	*ast_error(char *msg)
{
	t_ast	*error_node;

	error_node = ast_new(AST_ERROR, NULL);
	if (!error_node)
		return (NULL);
	error_node->error = ft_strdup(msg);
	if (!error_node->error)
		return (ast_free(error_node), NULL);
	return (error_node);
}
