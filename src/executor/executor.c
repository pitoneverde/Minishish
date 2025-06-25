/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 13:17:05 by plichota          #+#    #+#             */
/*   Updated: 2025/06/26 01:00:27 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_ast *ast)
{
	if (!ast || !ast->argv || !ast->argv[0])
		return (0);
	const char *cmd = ast->argv[0];
	return (
		ft_strcmp(cmd, "echo") == 0 ||
		ft_strcmp(cmd, "cd") == 0 ||
		ft_strcmp(cmd, "pwd") == 0 ||
		ft_strcmp(cmd, "export") == 0 ||
		ft_strcmp(cmd, "unset") == 0 ||
		ft_strcmp(cmd, "env") == 0 ||
		ft_strcmp(cmd, "exit") == 0
	);
}

int	executor(t_ast *ast, int fd_in, t_sh *shell, int is_fork)
{
	int status;
	(void) fd_in;

	status = 127;
	if (!ast || !shell)
		return (status);
	if (ast_is_command(ast))
	{
		if (is_fork)
			status = execute_command(ast, fd_in, shell);
		else
			status = spawn_command(ast, fd_in, shell);
	}
	else if (ast_is_simple_pipeline(ast))
		status = execute_pipeline(ast, STDIN_FILENO, shell);
	else if (ast_is_operator(ast))
		printf("operator\n"); // status = execute_operator()
	else if (ast_is_redirection_chain(ast))
		printf("redirection\n"); // status = execute_redirection
	else
		perror("Unknown node type");
	if (g_signal_status != 0)
	{
		shell->last_code = g_signal_status;
		g_signal_status = 0;
	}
	else if (!is_fork) // prendere solo status ultimo figlio (non forkato)
		shell->last_code = status;
	return (shell->last_code);
}
