/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:17:36 by plichota          #+#    #+#             */
/*   Updated: 2025/07/10 15:08:42 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int execute_builtin_exit(t_ast *ast, t_sh *shell)
{
	char **argv = ast->argv;
	long int exit_code = 0;

	ft_putendl_fd("exit", 2);
	if (argv[1] && !is_numeric(argv[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		free_all(shell);
		exit(255);
	}
	if (argv[1] && argv[2])
	{
		ft_putstr_fd("Too many arguments", 2);
		shell->last_code = 1;
		free_all(shell);
		return (1);
	}
	if (argv[1])
		exit_code = ft_atoi(argv[1]);
	free_all(shell);
	exit((unsigned char)exit_code);
}
