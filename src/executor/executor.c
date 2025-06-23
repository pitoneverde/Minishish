/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 13:17:05 by plichota          #+#    #+#             */
/*   Updated: 2025/06/23 18:11:19 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int execute_builtin(t_ast *ast, t_sh *shell)
{
	(void) shell;
	if (!ast || !ast->argv || !ast->argv[0])
		return (1);

	const char *cmd = ast->argv[0];

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
	execve(path, ast->argv, env_to_envp((*shell).env));
	free(path);
	perror("execve error");
	return (127); // to do controllare perche' fallisce (126 o 127)
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
	else
	{
		close(fd[1]);
		status = executor(ast->right, fd[0], shell);
		close(fd[0]);
		waitpid(pid, &status, 0);
		return (status);
	}
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


int    executor(t_ast *ast, int fd_in, t_sh *shell)
{
	int status;
	(void) fd_in;

	status = 127;
	if (!ast || !shell)
		return (status);
	if (ast_is_command(ast)) 
		status = spawn_command(ast, fd_in, shell);
	else if (ast_is_simple_pipeline(ast))
		status = execute_pipeline(ast, STDIN_FILENO, shell);
	else if (ast_is_operator(ast))
		printf("operator\n"); // status = execute_operator()
	else if (ast_is_redirection_chain(ast))
		printf("redirection\n"); // status = execute_redirection
	else
		perror("Unknown node type");

	shell->last_code = status;
	return (status);
}
