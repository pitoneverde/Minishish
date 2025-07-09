/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 13:17:05 by plichota          #+#    #+#             */
/*   Updated: 2025/07/09 22:56:43 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// chiama la funzione specifica per ogni builtin
// cmd = ast->argv[0]; // se è AST_COMMAND argv[0] == value
int execute_builtin(t_ast *ast, int fd_in, int fd_out, t_sh *shell)
{
	const char *cmd;
	int	used_fd_in;
	int	used_fd_out;

	(void) shell;
	used_fd_in = fd_in;
	used_fd_out = fd_out;
	override_fd_with_ctx(ast, &used_fd_in, &used_fd_out);
	if (!ast || !ast->argv || !ast->argv[0])
		return (1);
	cmd = ast->argv[0];
	if (ft_strcmp(cmd, "echo") == 0)
		return (execute_builtin_echo(ast, used_fd_out));
	if (ft_strcmp(cmd, "cd") == 0)
		return execute_builtin_cd(ast, shell);
	if (ft_strcmp(cmd, "pwd") == 0)
		return execute_builtin_pwd(ast, used_fd_out);
	if (ft_strcmp(cmd, "export") == 0)
		return execute_builtin_export(ast, used_fd_out, shell);
	if (ft_strcmp(cmd, "unset") == 0)
		return execute_builtin_unset(ast, shell);
	if (ft_strcmp(cmd, "env") == 0)
		return execute_builtin_env(ast, used_fd_out, shell);
	if (ft_strcmp(cmd, "exit") == 0)
		return execute_builtin_exit(ast, shell);
	return (1);
}

// int execute_operator(t_ast *ast, int fd_in, t_sh *shell)
// {
// 	int left_status;
	
// 	left_status = executor(ast->left, fd_in, shell);

// 	if (ft_strcmp(ast->value, "&&") == 0)
// 	{
// 		if (left_status == 0)
// 			return executor(ast->right, fd_in, shell);
// 		else
// 			return left_status;
// 	}
// 	else if (ft_strcmp(ast->value, "||") == 0)
// 	{
// 		if (left_status != 0)
// 			return executor(ast->right, fd_in, shell);
// 		else
// 			return left_status;
// 	}
// 	else
// 	{
// 		perror("Unsupported operator");
// 		return 127;
// 	}
// }
