/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 13:17:05 by plichota          #+#    #+#             */
/*   Updated: 2025/07/05 18:47:10 by plichota         ###   ########.fr       */
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
	if (ft_strcmp(cmd, "cd") == 0)
		return execute_builtin_cd(ast, shell);
	if (ft_strcmp(cmd, "pwd") == 0)
		return execute_builtin_pwd(ast);
	// if (ft_strcmp(cmd, "export") == 0)
	// 	return execute_builtin_export(ast, shell);
	// if (ft_strcmp(cmd, "unset") == 0)
	// 	return execute_builtin_unset(ast, shell);
	if (ft_strcmp(cmd, "env") == 0)
		return execute_builtin_env(ast, shell);
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
