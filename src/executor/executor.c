/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 13:17:05 by plichota          #+#    #+#             */
/*   Updated: 2025/07/14 17:14:37 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_ast *ast)
{
	const char	*cmd;
	int			is_builtin;

	is_builtin = 0;
	if (!ast || !ast->argv || !ast->argv[0])
		return (0);
	cmd = ast->argv[0];
	if (
		ft_strcmp(cmd, "echo") == 0
		|| ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "pwd") == 0
		|| ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0
		|| ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "exit") == 0
	)
		is_builtin = 1;
	return (is_builtin);
}

int	dispatch_command(t_ast *ast, t_sh *shell)
{
	int	status;

	if (shell->process.is_fork)
	{
		if (is_builtin(ast))
			status = execute_builtin(ast, shell);
		else
			status = execute_command(ast, shell);
	}
	else
		status = spawn_command(ast, shell);
	if (status == EXIT_SIGQUIT)
		write(STDERR_FILENO, "Quit (core dumped)\n", 19);
	return (status);
}

int	executor(t_ast *ast, t_sh *shell)
{
	int	status;

	status = 127;
	if (!ast || !shell)
		return (status);
	if (ast_is_redirection(ast))
		return (executor(ast->left, shell));
	if (ast_is_simple_pipeline(ast) || ast->type == AST_PIPE)
		status = execute_pipeline(ast, shell);
	else if (ast_is_command(ast))
		status = dispatch_command(ast, shell);
	else
		return (0);
	update_signal_status(shell);
	if (!shell->process.is_fork)
		shell->last_code = status;
	return (shell->last_code);
}
