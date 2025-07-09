/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 18:39:34 by plichota          #+#    #+#             */
/*   Updated: 2025/07/09 22:52:33 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// stampa tutte le variabili env esportabili
int		execute_builtin_env(t_ast *ast, int fd_out, t_sh *shell)
{
	t_list	*node;
	t_env	*entry;

	if (!ast)
		return(perror("ast error"), 1);
	if (ast->argc > 1)
		return (perror("env: too many arguments"), 1);
	node = shell->env;
	while (node != NULL)
	{
		entry = (t_env *)node->content;
		if (entry->exported && entry->value)
		{
			ft_putstr_fd(entry->key, fd_out);
			ft_putchar_fd('=', fd_out);
			ft_putstr_fd(entry->value, fd_out);
			ft_putchar_fd('\n', fd_out);
		}
		node = node->next;
	}
	return (0);
}
