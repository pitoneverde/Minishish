/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 18:48:47 by plichota          #+#    #+#             */
/*   Updated: 2025/07/12 22:48:18 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// stampa tutte le env ordinate (sia esportabili che non)
// oppure upsert variabili in formato valido
// con la dicitura declare -x VAR="value"
// se var non esiste la crea
int	execute_builtin_export(t_ast *ast, int fd_out, t_sh *shell)
{
	int		i;
	char	*key;
	char	*value;

	if (ast->argc == 1)
		return (print_env_export(shell->env, fd_out));
	i = 1;
	while (i < ast->argc)
	{
		split_env(ast->argv[i], &key, &value);
		if (!is_valid_var_name(key))
		{
			perror("bash: export: not a valid identifier");
			i++;
			continue ;
		}
		set_env_var(&(shell->env), key, value, 1);
		if (key)
			free(key);
		if (value)
			free(value);
		i++;
	}
	return (0);
}
