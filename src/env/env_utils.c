/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 04:15:39 by sabruma           #+#    #+#             */
/*   Updated: 2025/07/05 23:00:04 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	unset_env_var(t_list **env, const char *key)
{
	t_list	*prev;
	t_list	*curr;
	t_env	*entry;

	if (!env || !key || !*key)
		return ;
	prev = NULL;
	curr = *env;
	while (curr)
	{
		entry = (t_env *)curr->content;
		if (!ft_strcmp(entry->key, key))
		{
			if (prev)
				prev->next = curr->next;
			else
				*env = curr->next;
			free_env_entry(entry);
			free(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

/// @brief gets the value of a t_env variable
/// @param env context, list of t_env
/// @param key must be NULL-terminated 
/// @return value of variable
char	*get_env_value(const t_list *env, const char *key)
{
	t_env	*entry;

	if (!env || !key || !*key)
		return (NULL);
	while (env)
	{
		entry = (t_env *)env->content;
		if (!ft_strcmp(entry->key, key))
			return (entry->value);
		env = env->next;
	}
	return (NULL);
}

void	set_env_var(t_list **env, const char *key, const char *val, int exp)
{
	t_list	*curr;
	t_env	*entry;

	if (!env || !key || !*key)
		return ;
	curr = *env;
	while (curr)
	{
		entry = curr->content;
		if (may_re_env_var(entry, key, val, exp))
			return ;
		curr = curr->next;
	}
	entry = (t_env *)malloc(sizeof(t_env));
	if (!entry)
		return ;
	entry->key = ft_strdup(key);
	entry->value = strdup_safe(val);
	entry->exported = exp;
	ft_lstadd_back(env, ft_lstnew(entry));
}

void	*env_to_str(void *ptr)
{
	t_env	*entry;
	char	*joined;
	char	*temp;

	entry = (t_env *)ptr;
	if (!entry->exported)
		return (NULL);
	temp = ft_strjoin(entry->key, "=");
	if (!temp)
		return (NULL);
	joined = ft_strjoin(temp, entry->value);
	free(temp);
	return (joined);
}
