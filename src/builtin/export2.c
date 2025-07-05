/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 18:48:47 by plichota          #+#    #+#             */
/*   Updated: 2025/07/05 21:44:37 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_export_entry(char *entry)
{
	const char	*equal;

	if (!entry)
		return ;
	ft_putstr_fd("declare -x ", 1);
	equal = ft_strchr(entry, '=');
	if (!equal)
	{
		ft_putstr_fd(entry, 1);
		ft_putchar_fd('\n', 1);
		return ;
	}
	while (*entry && *entry != '=')
	{
		ft_putchar_fd(*entry, 1);
		entry++;
	}
	ft_putstr_fd("=\"", 1);
	ft_putstr_fd(entry + 1, 1);
	ft_putstr_fd("\"\n", 1);
}

void	print_export_arr(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		print_export_entry(arr[i]);
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
int	print_env_export(t_list *env)
{
	char	**arr;

	arr = env_to_envp(env);
	if (!arr)
		return (perror("env to envp"), 1);
	bubble_sort_arr(arr);
	print_export_arr(arr);
	free_envp(arr);
	return (0);
}