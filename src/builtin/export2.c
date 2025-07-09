/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 18:48:47 by plichota          #+#    #+#             */
/*   Updated: 2025/07/09 22:51:45 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_export_entry(char *entry, int fd_out)
{
	const char	*equal;

	if (!entry)
		return ;
	ft_putstr_fd("declare -x ", fd_out);
	equal = ft_strchr(entry, '=');
	if (!equal)
	{
		ft_putstr_fd(entry, fd_out);
		ft_putchar_fd('\n', fd_out);
		return ;
	}
	while (*entry && *entry != '=')
	{
		ft_putchar_fd(*entry, fd_out);
		entry++;
	}
	ft_putstr_fd("=\"", fd_out);
	ft_putstr_fd(entry + 1, fd_out);
	ft_putstr_fd("\"\n", fd_out);
}

void	print_export_arr(char **arr, int fd_out)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		print_export_entry(arr[i], fd_out);
		i++;
	}
}

// sorta un array di array con bubble sort
// compara ogni entry con quella successiva
// se maggiore swappa
void	bubble_sort_arr(char **arr)
{
	int		i;
	int		sorted;
	char	*tmp;

	if (!arr)
		return ;
	sorted = 0;
	while (!sorted)
	{
		sorted = 1;
		i = 0;
		while (arr[i] && arr[i + 1])
		{
			if (ft_strcmp(arr[i], arr[i + 1]) > 0)
			{
				tmp = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = tmp;
				sorted = 0;
			}
			i++;
		}
	}
}

// crea una array di "VAR=value"
// ordina col bubble sort
// stampa le entries con la dicitura declare -x VAR="value"
int	print_env_export(t_list *env, int fd_out)
{
	char	**arr;

	arr = env_to_envp(env);
	if (!arr)
		return (perror("env to envp"), 1);
	bubble_sort_arr(arr);
	print_export_arr(arr, fd_out);
	mtxfree_str(arr);
	return (0);
}

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
