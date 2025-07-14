/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 13:17:05 by plichota          #+#    #+#             */
/*   Updated: 2025/07/14 15:45:20 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_pipe_child(int *fd, t_ast *ast, t_sh *shell)
{
	int	status;

	set_default_signals();
	close(fd[0]);
	if (fd[1] != STDOUT_FILENO)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
	if (shell->process.fd_in != STDIN_FILENO)
	{
		dup2(shell->process.fd_in, STDIN_FILENO);
		close(shell->process.fd_in);
	}
	shell->process.is_fork = 1;
	shell->process.is_in_pipeline = 1;
	status = executor(ast->left, shell);
	free_all(shell);
	exit(status);
}

int	handle_pipe_parent(int *fd, pid_t left_pid, t_sh *shell, t_ast *ast)
{
	int	status;

	ignore_signals();
	close(fd[1]);
	shell->process.fd_in = fd[0];
	shell->process.fd_out = STDOUT_FILENO;
	shell->process.is_fork = 0;
	shell->process.is_in_pipeline = 1;
	status = executor(ast->right, shell);
	close(fd[0]);
	waitpid(left_pid, NULL, 0);
	init_signals();
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
		g_last_signal = WTERMSIG(status);
		update_signal_status(shell);
		return (shell->last_code);
	}
	else
		return (status);
}

// crea una pipe che legge dal nodo sinistro e scrive nel destro
// se e' una pipeline forkata esce col risultato di executor
// TO DO trovare modo di gestire il wait per tutti nel root
int	execute_pipeline(t_ast *ast, t_sh *shell)
{
	int		fd[2];
	pid_t	left_pid;

	if (!ast || !ast->left || !ast->right)
		return (127);
	if (pipe(fd) == -1)
		return (perror("pipe failed"), 1);
	left_pid = fork();
	if (left_pid < 0)
	{
		close(fd[0]);
		close(fd[1]);
		return (perror("fork"), 127);
	}
	else if (left_pid == 0)
	{
		handle_pipe_child(fd, ast, shell);
	}
	return (handle_pipe_parent(fd, left_pid, shell, ast));
}
