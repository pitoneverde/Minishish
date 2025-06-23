/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:17:36 by plichota          #+#    #+#             */
/*   Updated: 2025/06/23 18:11:15 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int is_numeric(const char *str)
{
	int i = 0;

	if (!str)
		return (0);
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

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
		exit(255);
	}
	if (argv[1] && argv[2])
	{
		perror("Too many arguments");
		shell->last_code = 1;
		return (1);
	}
	if (argv[1])
		exit_code = ft_atoi(argv[1]);
	exit((unsigned char)exit_code);
}
