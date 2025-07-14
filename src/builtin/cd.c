/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 15:30:57 by plichota          #+#    #+#             */
/*   Updated: 2025/07/12 22:43:23 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// aggiorna gli env PWD (esportabile) e OLDPWD (non esportabile)
void	update_pwd_env(t_sh *shell, char *oldpwd)
{
	char	*newpwd;

	if (!oldpwd)
		return ;
	newpwd = getcwd(NULL, 0);
	if (!newpwd)
		return (free(oldpwd));
	set_env_var(&shell->env, "PWD", newpwd, 1);
	set_env_var(&shell->env, "OLDPWD", oldpwd, 0);
	free(oldpwd);
	free(newpwd);
}

// cd . aggiorna oldpwd
// cd .. ritorno alla cartella padre
// cd - torna a oldpwd (NON GESTITO)
// cd ~ va a home (NON GESTITO)
int	execute_builtin_cd(t_ast *ast, t_sh *shell)
{
	char	*path;
	char	*oldpwd;

	if (!ast)
		return (perror("Ast error"), 1);
	if (ast->argc > 2)
		return (perror("Too many arguments"), 1);
	if (ast->argc == 1)
		path = get_env_value(shell->env, "HOME");
	else
		path = ast->argv[1];
	if (!path)
		return (perror("HOME not set"), 1);
	oldpwd = getcwd(NULL, 0);
	if (chdir(path) != 0)
	{
		free(oldpwd);
		perror("cd");
		return (1);
	}
	update_pwd_env(shell, oldpwd);
	return (0);
}
