/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 13:17:05 by plichota          #+#    #+#             */
/*   Updated: 2025/06/29 23:44:56 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// if cmd contains a '/' returns
// otherwise split all the paths and check them one by one
char	*search_path(char *cmd, t_sh *shell)
{
	char *paths;
	char **split_paths;

	if (!cmd || !shell)
		return (NULL);
	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	paths = get_env_value(shell->env, "PATH");
	if (!paths)
		return (NULL);
	split_paths = ft_split(paths, ':');
	free(paths);
	if (!split_paths)
		return (NULL);
	return (find_command_path(cmd, split_paths));
}

char *find_command_path(char *cmd, char **paths)
{
	int i;
	char *temp;
	char *full_path;
	
	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(temp, cmd);
		free(temp);
		if (access(full_path, X_OK) == 0)
		{
			mtxfree_str(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	mtxfree_str(paths);
	return (temp);
}

int spawn_command(t_ast *ast, int fd_in, int fd_out, t_sh *shell, int is_in_pipeline)
{
	pid_t pid;
	int status;

	if (is_builtin(ast) && !is_in_pipeline)
		return (execute_builtin(ast, shell));
	// write(2, "spawn\n", 6);
	pid = fork(); 
	if (pid < 0)
		return (1); // to do gestire errore
	if (pid == 0)
	{
		if (is_builtin(ast))
			return (execute_builtin(ast, shell));
		execute_command(ast, fd_in, fd_out, shell); // esce da solo
	}
	// ferma il waitpid del padre assoluto
	// if (!is_last_child(ast))
	// 	return (-1);

	// to do spostare dopo l'esecuzione di tutti i comandi 
	// aspetta tutti i figli forkati (da solo si da' -1 quando i figli sono finiti)
	// while (waitpid(-1, &status, 0) != -1) per l'ultimo figlio
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status)); 
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	else
		return (1); // to do gestire errore
}

int	execute_command(t_ast *ast, int fd_in, int fd_out, t_sh *shell)
{
	char	*path;

	// write(2, "exec\n", 5);
	if (!ast || !ast->argv || !ast->argv[0])
	{
		perror("Invalid node");
		exit(1);
	}
	if (fd_in != STDIN_FILENO)
	{
		if (dup2(fd_in, STDIN_FILENO) == -1)
		{
			perror("dup2 failed");
			exit (1);
		}
		close(fd_in); // Are we sure?
	}
	if (fd_out != STDOUT_FILENO)
	{
		if (dup2(fd_out, STDOUT_FILENO) == -1)
		{
			perror("dup2 failed");
			exit (1);
		}
		close(fd_out); // Are we sure?
	}
	path = search_path(ast->argv[0], shell);
	if (!path)
		exit (127);
	// metter envp in var a parte -> rischio leaks
	execve(path, ast->argv, env_to_envp(shell->env));
	// free_envp()
	free(path); // to do aggiustare
	perror("execve error");
	exit(127); // to do controllare EACCESS (126 o 127)
}
