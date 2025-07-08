/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 13:17:05 by plichota          #+#    #+#             */
/*   Updated: 2025/07/09 00:15:12 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_command_access(char *path)
{
	if (access(path, F_OK) == -1) {
		perror("No such file or directory");
		// TO DO  ft_printf_fd(STDERR_FILENO, "minishell: %s: No such file or directory\n", path);
		return (0);
	}
	if (access(path, X_OK) == -1) {
		perror("Permission denied");
		// ft_printf_fd(STDERR_FILENO, "minishell: %s: Permission denied\n", path);
		return (0);
	}
	return (1);
}

// For every path in PATH, check if cmd works
char *find_command_path(char *cmd, char **paths)
{
	int i;
	char *temp;
	char *full_path;
	
	if (!cmd || !*cmd || !paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		if (!temp)
			return (NULL);
		full_path = ft_strjoin(temp, cmd);
		free(temp);
		if (!full_path)
			return (NULL);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

// if cmd contains a '/' returns cmd
// otherwise split all the paths and check them one by one
// 
char	*search_path(char *cmd, t_sh *shell)
{
	char *res;
	char *env_paths;
	char **split_paths;

	if (!cmd || !*cmd || !shell)
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK) == 0)
			return (ft_strdup(cmd));
		perror("Command not found or permission denied");
		// ft_printf_fd(STDERR_FILENO, "minishell: %s: command not found or permission denied\n", cmd);
		return (NULL);
	}
	env_paths = get_env_value(shell->env, "PATH");
	if (!env_paths)
		return (NULL);
	split_paths = ft_split(env_paths, ':');
	free(env_paths);
	if (!split_paths)
		return (NULL);
	res = find_command_path(cmd, split_paths);
	mtxfree_str(split_paths);
	return (res);
}

// crea e gestisce il fork
int spawn_command(t_ast *ast, int fd_in, int fd_out, t_sh *shell, int is_in_pipeline)
{
	pid_t pid;
	int status;

	if (!ast || !ast->argv || !ast->argv[0] || !shell)
		return (1);
	if (is_builtin(ast) && !is_in_pipeline)
		return (execute_builtin(ast, fd_out, shell));
	pid = fork(); 
	if (pid < 0)
		return (1); // to do gestire errore
	if (pid == 0)
	{
		if (is_builtin(ast))
			exit(execute_builtin(ast, fd_out, shell));
		execute_command(ast, fd_in, fd_out, shell); // esce da solo
	}
	// ferma il waitpid del padre assoluto
	// if (!is_last_child(ast))
	// 	return (-1);

	// to do spostare dopo l'esecuzione di tutti i comandi 
	// aspetta tutti i figli forkati (da solo si da' -1 quando i figli sono finiti)
	// while (waitpid(-1, &status, 0) != -1) per l'ultimo figlio
	if (waitpid(pid, &status, 0) == -1) { // gestisco pid inesistente, zombie e processi gia' terminati
		perror("waitpid failed");
		return (1);
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status)); 
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	else
		return (1); // to do gestire errore
}

// effettua redirezioni ed esegue comando
int	execute_command(t_ast *ast, int fd_in, int fd_out, t_sh *shell)
{
	char	*path;
	char	**envp;

	if (!ast || !ast->argv || !ast->argv[0])
	{
		perror("Invalid node");
		exit(1);
	}
	override_fd_with_ctx(ast, &fd_in, &fd_out);
	set_std_fd(fd_in, fd_out);
	path = search_path(ast->argv[0], shell);
	// to do caso non c'e path
	envp = env_to_envp(shell->env);
	if (!path || !envp)
		cleanup_and_exit(path, envp, EXIT_CMD_NOT_FOUND, "command not found");
	if (!check_command_access(path))
		cleanup_and_exit(path, envp, EXIT_PERMISSION_DENIED, "Permission denied");
	execve(path, ast->argv, envp);
	cleanup_and_exit(path, envp, EXIT_PERMISSION_DENIED, "???"); // TO DO
	return (1);
}
