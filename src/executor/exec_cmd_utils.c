/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 13:17:05 by plichota          #+#    #+#             */
/*   Updated: 2025/07/14 15:02:09 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_command_access(char *path)
{
	if (access(path, F_OK) == -1)
	{
		perror("No such file or directory");
		return (0);
	}
	if (access(path, X_OK) == -1)
	{
		perror("Permission denied");
		return (0);
	}
	return (1);
}

// For every path in PATH, check if cmd works
char	*find_command_path(char *cmd, char **paths)
{
	int		i;
	char	*temp;
	char	*full_path;

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
// free(env_paths);
// DO NOT FREE RESULT OF get_env_value: it returns an internal
// pointer variable (it will leak + invalid read)
char	*search_path(char *cmd, t_sh *shell)
{
	char	*res;
	char	*env_paths;
	char	**split_paths;

	if (!cmd || !*cmd || !shell)
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK) == 0)
			return (ft_strdup(cmd));
		perror("Command not found or permission denied");
		return (NULL);
	}
	env_paths = get_env_value(shell->env, "PATH");
	if (!env_paths)
		return (NULL);
	split_paths = ft_split(env_paths, ':');
	if (!split_paths)
		return (NULL);
	res = find_command_path(cmd, split_paths);
	mtxfree_str(split_paths);
	return (res);
}

void	init_process_data(t_ast *ast, t_sh *shell)
{
	t_process_data	*process;

	process = &shell->process;
	override_fd_with_ctx(ast, &process->fd_in, &process->fd_out);
	set_std_fd(process->fd_in, process->fd_out);
	close_unused_fds(ast, process->fd_in, process->fd_out);
	process->path = search_path(ast->argv[0], shell);
	process->envp = env_to_envp(shell->env);
}
