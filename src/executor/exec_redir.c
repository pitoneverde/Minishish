/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 18:50:48 by plichota          #+#    #+#             */
/*   Updated: 2025/07/05 23:41:18 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// apre i file e imposta fd_in/fd_out (poi spawn_command e execute_command faranno il resto)
int execute_redirection_chain(t_ast *ast, t_sh *shell, int is_fork, int is_in_pipeline)
{
	int status = 0;
	int fd;

	if (!ast || !shell)
		return (127);

	if (ast->type == AST_REDIR_IN)
	{
		fd = handle_redir_in(ast, shell);
		if (fd == -1)
			return (1);
		// chiamo executor
	} else if (ast->type == AST_REDIR_OUT)
	{
		fd = handle_redir_out(ast, shell);
		if (fd == -1)
			return (1);
		// chiama executor
	} else if (ast->type == AST_APPEND)
	{
		fd = handle_append(ast, shell);
		if (fd == -1)
			return (1);
		// chiama executor
	} else if (ast->type == AST_HEREDOC)
	{
		fd = handle_heredoc(ast, shell);
		if (fd == -1)
			return (1);
		// chiama executor
	} else
		return (perror("Unknown redirection type"), 1); // to do ft_printf_fd

	return (0);
}