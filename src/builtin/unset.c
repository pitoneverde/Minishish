/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 22:52:29 by plichota          #+#    #+#             */
/*   Updated: 2025/07/09 22:52:18 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_builtin_unset(t_ast *ast, t_sh *shell)
{
	int	i;

	if (!ast || !shell || !ast->argv)
		return (1);
	i = 1;
	while (ast->argv[i])
	{
		unset_env_var(&shell->env, ast->argv[i]);
		i++;
	}
	return (0);
}
