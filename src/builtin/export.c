/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 18:48:47 by plichota          #+#    #+#             */
/*   Updated: 2025/07/05 22:52:17 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// splitto la stringa in chiave e valore con attenzione agli edge cases
void	split_env(char *str, char **key, char **val)
{
	char	*equal;

	equal = ft_strchr(str, '=');
	if (!equal)
	{
		*key = ft_strdup(str);
		*val = NULL;
	}
	else
	{
		*key = ft_substr(str, 0, equal - str);
		*val = ft_strdup(equal + 1);
	}
}

// stampa tutte le env ordinate (sia esportabili che non)
// oppure upsert variabili in formato valido
// con la dicitura declare -x VAR="value"
// se var non esiste la crea
int	execute_builtin_export(t_ast *ast, t_sh *shell)
{
	int		i;
	char	*key;
	char	*value;

	if (ast->argc == 1)
		return (print_env_export(shell->env));
	i = 1;
	while (i < ast->argc)
	{
		split_env(ast->argv[i], &key, &value);
		if (!is_valid_var_name(key))
		{
			perror("not a valid identifier"); // to do fprintf bash: export: `12VAR=dksf': not a valid identifier
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
