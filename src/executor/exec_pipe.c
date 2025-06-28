/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 13:17:05 by plichota          #+#    #+#             */
/*   Updated: 2025/06/28 23:47:25 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// crea una pipe che legge dal nodo sinistro e scrive nel destro
// se e' una pipeline forkata esce col risultato di executor
// TO DO trovare modo di gestire il wait per tutti nel root
int	execute_pipeline(t_ast *ast, int fd_in, int fd_out, t_sh *shell)
{
	int		fd[2];
	pid_t	left_pid;
	int 	status;

	if (!ast || !ast->left || !ast->right)
		return (127);
	if (pipe(fd) == -1)	
		return (perror("pipe failed"), 1);
	left_pid = fork();
	if (left_pid < 0)
	{
		// to do chiudere fd pipe
		return (perror("fork"), 127);
	}
	else if (left_pid == 0)
	{
		close(fd[0]);
		if (fd[1] != STDOUT_FILENO)
		{
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
		}
		if (fd_in != STDIN_FILENO)
		{
			dup2(fd_in, STDIN_FILENO);
			close(fd_in);
		}
		exit(executor(ast->left, fd_in, STDOUT_FILENO, shell, 1));
	}
	close(fd[1]);
	status = executor(ast->right, fd[0], fd_out, shell, 0);
	close(fd[0]);
	// non ci interessa lo status dei nodi a sinistra
	waitpid(left_pid, NULL, 0);
	return (status);
}
