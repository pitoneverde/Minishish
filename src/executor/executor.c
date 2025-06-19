/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 13:17:05 by plichota          #+#    #+#             */
/*   Updated: 2025/06/19 18:08:04 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// To do
int execute_builtin(ast)
{
    printf("exec builtin\n");
    return (0);

}

int	is_builtin(t_ast *ast)
{
	// ◦ echo with option -n
	// ◦ cd with only a relative or absolute path
	// ◦ pwd with no options
	// ◦ export with no options
	// ◦ unset with no options
	// ◦ env with no options or arguments
	// ◦ exit with no options
	return (0);
}

int spawn_command(t_ast *ast, int fd_in, t_sh *shell)
{
    pid_t pid;
    int status;

    if (is_builtin(ast))
        return (execute_builtin(ast));
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

char	*search_path(char *cmd, t_sh *shell)
{
	// prendi path
	char *path = get_env_value(shell->env, "PATH");
	// strtok path
	// scorrere path
	// per ogni token controlla se path/cmd esiste
	// se esiste restituisci path 
	// get path from shell.env
	// Scorro t_list (ogni nodo contiene content e next)
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
	path = search_path(ast->argv[0], (*shell).env);
	if (!path)
	{
		perror("path not found");
		return (127);
	}
	execve(path, ast->argv, env_to_envp((*shell).env));
	free(path);
    perror("execvp error");
	return (127); // to do controllare perche' fallisce (126 o 127)
}

int	execute_pipeline(t_ast *ast, int fd_in, t_sh *shell)
{
	int	fd[2];
	pid_t	pid;
	int status;

	// controllo ast
	
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
	else if (pid > 0)
	{
		close(fd[1]);
		status = executor(ast->right, fd_in, shell);
		close(fd[0]);
		waitpid(pid, &status, 0);
		return (status);
	}
}

int    executor(t_ast *ast, int fd_in, t_sh *shell)
{
    if (!ast)
        return (127);
    if (ast_is_command(ast)) 
	{
        shell->last_code = spawn_command(ast, STDIN_FILENO, shell);
        return (shell->last_code);
	}
    else if (ast_is_simple_pipeline(ast))
    {
        shell->last_code = execute_pipeline(ast, STDIN_FILENO, shell);
        return (shell->last_code);
    }
	else if (ast_is_operator(ast))
	{
		printf("operator\n");
	}
	else if (ast_is_redirection_chain(ast))
	{
		printf("redirection\n");
	}
	else
	{
		print_error("Unknown node type");
	}
    return (127);
}
