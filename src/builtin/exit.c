/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:17:36 by plichota          #+#    #+#             */
/*   Updated: 2025/07/12 22:47:54 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// if no args:
// - exit with last code
// if 1 arg:
// - if numeric, exit with arg (value%255)
// - if NOT numeric, print error and exit with 255
// if >1 arg:
// print error and
// - if first numeric, do NOT exit, return 1
// - if first NOT numeric, exit with 255
int	execute_builtin_exit(t_ast *ast, t_sh *shell)
{
	char		**argv;
	long int	exit_code;

	exit_code = 0;
	argv = ast->argv;
	ft_putendl_fd("exit", 2);
	if (argv[1] && !is_numeric(argv[1]))
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(argv[1], 2);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		free_all(shell);
		exit(255);
	}
	if (argv[1] && argv[2])
	{
		ft_putstr_fd("Too many arguments\n", 2);
		shell->last_code = 1;
		return (1);
	}
	if (argv[1])
		exit_code = ft_atoi(argv[1]);
	free_all(shell);
	exit((unsigned char)exit_code);
}
