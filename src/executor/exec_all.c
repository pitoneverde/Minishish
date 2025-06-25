/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 13:17:05 by plichota          #+#    #+#             */
/*   Updated: 2025/06/25 18:41:09 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int execute_builtin(t_ast *ast, t_sh *shell)
{
	(void) shell;
	if (!ast || !ast->argv || !ast->argv[0])
		return (1);

	const char *cmd = ast->argv[0]; // se è AST_COMMAND argv[0] == value

	if (ft_strcmp(cmd, "echo") == 0)
		return (execute_builtin_echo(ast));
	// if (ft_strcmp(cmd, "cd") == 0)
	// 	return execute_builtin_cd(ast, shell);
	if (ft_strcmp(cmd, "pwd") == 0)
		return execute_builtin_pwd(ast);
	// if (ft_strcmp(cmd, "export") == 0)
	// 	return execute_builtin_export(ast, shell);
	// if (ft_strcmp(cmd, "unset") == 0)
	// 	return execute_builtin_unset(ast, shell);
	// if (ft_strcmp(cmd, "env") == 0)
	// 	return execute_builtin_env(shell);
	if (ft_strcmp(cmd, "exit") == 0)
		return execute_builtin_exit(ast, shell);

	return (1);
}

int	execute_pipeline(t_ast *ast, int fd_in, t_sh *shell)
{
	int	fd[2];
	pid_t	pid;
	int status;

	// controllo ast
	if (!ast)
		return (127);
	// redirect pipe
	if (pipe(fd) == -1)
		return (perror("pipe failed"), 1); // controllare errore
	// forko left ed eseguo
	// chiudo fd
	pid = fork();
	if (pid < 0)
		return (perror("fork"), 1);
	else if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		exit(executor(ast->left, fd_in, shell));
	}
	close(fd[1]);
	status = executor(ast->right, fd[0], shell);
	close(fd[0]);
	waitpid(pid, &status, 0);
	return (status);
}

int execute_operator(t_ast *ast, int fd_in, t_sh *shell)
{
	int left_status;
	
	left_status = executor(ast->left, fd_in, shell);

	if (ft_strcmp(ast->value, "&&") == 0)
	{
		if (left_status == 0)
			return executor(ast->right, fd_in, shell);
		else
			return left_status;
	}
	else if (ft_strcmp(ast->value, "||") == 0)
	{
		if (left_status != 0)
			return executor(ast->right, fd_in, shell);
		else
			return left_status;
	}
	else
	{
		perror("Unsupported operator");
		return 127;
	}
}
