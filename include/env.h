/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 20:03:36 by sabruma           #+#    #+#             */
/*   Updated: 2025/07/07 13:48:12 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(ENV_H)
# define ENV_H

# include "matrix.h"
# include "list.h"
# include "strings.h"
# include "chars.h"
# include <unistd.h>

typedef struct s_env
{
	char	*key;
	char	*value;
	int		exported;
}	t_env;

// core
t_list	*envp_to_env(char **envp);
char	**env_to_envp(t_list *env);
void	free_env(t_list *env);
void	free_env_entry(void *entry);

// utils, assume that key AKA variable name is valid
// validate input into builtin
void	*env_to_str(void *ptr);
void	unset_env_var(t_list **env, const char *key);
char	*get_env_value(const t_list *env, const char *key);
void	set_env_var(t_list **env, const char *key, const char *val, int exp);

// internal
int		may_re_env_var(t_env *entry, const char *key, const char *val, int exp);
int		is_valid_var_name(const char *name);
char	*strdup_safe(const char *str);
void	free_key_val_inc(char *key, char *val, int *i);

#endif // !ENV_H