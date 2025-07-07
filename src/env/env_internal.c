/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_internal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 04:26:22 by sabruma           #+#    #+#             */
/*   Updated: 2025/07/07 15:34:15 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include <stdio.h>

char	*strdup_safe(const char *str)
{
	if (!str)
		return (ft_strdup(""));
	return (ft_strdup(str));
}

int	may_re_env_var(t_env *entry, const char *key, const char *val, int exp)
{
	if (!ft_strcmp(entry->key, key))
	{
		free(entry->value);
		entry->value = strdup_safe(val);
		entry->exported = exp;
		return (1);
	}
	return (0);
}

void	free_key_val_inc(char *key, char *val, int *i)
{
	free(key);
	free(val);
	(*i)++;
}

// must be NULL-terminated
int	is_valid_var_name(const char *name)
{
	if (!name || !*name)
		return (0);
	if (!ft_isalpha(*name) && *name != '_')
		return (0);
	while (*name && *name != ' ')
	{
		if (!ft_isalnum(*name) && *name != '_')
			return (0);
		name++;
	}
	return (1);
}
