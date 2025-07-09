/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 16:13:58 by plichota          #+#    #+#             */
/*   Updated: 2025/07/09 22:51:17 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_builtin_pwd(t_ast *ast, int fd_out)
{
	char	*path;

	if (ast->argv[1])
	{
		perror("Too many arguments");
		return (1);
	}
	path = getcwd(NULL, 0);
	if (!path)
	{
		perror("pwd");
		return (1);
	}
	ft_putendl_fd(path, fd_out);
	free(path);
	return (0);
}
