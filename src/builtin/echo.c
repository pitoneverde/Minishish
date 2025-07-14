/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:47:07 by plichota          #+#    #+#             */
/*   Updated: 2025/07/12 22:45:01 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_flag_n(const char *arg)
{
	int	i;

	if (!arg || arg[0] != '-' || arg[1] != 'n')
		return (0);
	i = 2;
	while (arg[i] == 'n')
		i++;
	return (arg[i] == '\0');
}

int	execute_builtin_echo(t_ast *ast, int fd_out)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	while (ast->argv[i] && is_valid_flag_n(ast->argv[i]))
	{
		newline = 0;
		i++;
	}
	while (ast->argv[i])
	{
		ft_putstr_fd(ast->argv[i], fd_out);
		if (ast->argv[i + 1])
			ft_putchar_fd(' ', fd_out);
		i++;
	}
	if (newline)
		ft_putchar_fd('\n', fd_out);
	return (0);
}
