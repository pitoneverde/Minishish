/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 13:17:05 by plichota          #+#    #+#             */
/*   Updated: 2025/06/25 17:02:50 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// if cmd contains a '/' return
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

int spawn_command(t_ast *ast, int fd_in, t_sh *shell)
{
	pid_t pid;
	int status;

	if (is_builtin(ast))
		return (execute_builtin(ast, shell));
	pid = fork(); 
	if (pid < 0)
		return (1); // to do gestire errore
	if (pid == 0)
	{
		execute_command(ast, fd_in, shell);
		exit(1);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	else
		return (1); // to do gestire errore
}

int	execute_command(t_ast *ast, int fd_in, t_sh *shell)
{
	char	*path;

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
			return (1);
		}
		close(fd_in);
	}
	path = search_path(ast->argv[0], shell);
	if (!path)
	{
		perror("path not found");
		return (127);
	}
	execve(path, ast->argv, env_to_envp(shell->env));
	free(path);
	perror("execve error");
	return (127); // to do controllare perche' fallisce (126 o 127)
}
