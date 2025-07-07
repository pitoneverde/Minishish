/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 04:28:57 by sabruma           #+#    #+#             */
/*   Updated: 2025/07/07 15:33:59 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

t_list	*envp_to_env(char **envp)
{
	int		i;
	t_list	*env;
	char	*eq;
	char	*key;
	char	*val;

	env = NULL;
	i = 0;
	while (envp[i])
	{
		eq = ft_strchr(envp[i++], '=');
		if (!eq)
			continue ;
		i--;
		key = ft_substr(envp[i], 0, eq - envp[i]);
		val = ft_strdup(eq + 1);
		if (!key || !val)
		{
			free_key_val_inc(key, val, &i);
			continue ;
		}
		set_env_var(&env, key, val, 1);
		free_key_val_inc(key, val, &i);
	}
	return (env);
}

char	**env_to_envp(t_list *env)
{
	size_t	i;
	size_t	count;
	t_env	*entry;
	char	**envp;

	i = 0;
	count = ft_lstsize(env);
	envp = (char **)malloc(sizeof(char *) * (count + 1));
	if (!envp)
		return (NULL);
	while (env)
	{
		entry = env->content;
		if (entry->exported)
			envp[i++] = env_to_str(entry);
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}

void	free_env(t_list *env)
{
	ft_lstclear(&env, free_env_entry);
}

void	free_env_entry(void *entry)
{
	t_env	*var;

	if (!entry)
		return ;
	var = (t_env *)entry;
	free(var->key);
	free(var->value);
	free(var);
}
