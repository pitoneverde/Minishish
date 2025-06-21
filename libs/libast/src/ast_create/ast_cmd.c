/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 22:33:02 by sabruma           #+#    #+#             */
/*   Updated: 2025/06/21 22:33:09 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

// create command node
// args must be a list of AST_LITERAL nodes
t_ast	*ast_cmd(t_list *args)
{
	t_ast	*cmd;

	cmd = ast_new(AST_COMMAND, NULL);
	if (!cmd)
		return (NULL);
	cmd->args = args;
	cmd->argc = ft_lstsize(args);
	if (cmd->argc > 0)
		cmd->value = ft_strdup(((t_ast *)args->content)->value);
	return (cmd);
}
