#ifndef ENV_H
# define ENV_H

# include "matrix.h"
# include "list.h"
# include "strings.h"
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

// utils
void	unset_env_var(t_list **env, const char *key);
char	*get_env_value(const t_list *env, const char *key);
void	set_env_var(t_list **env, const char *key, const char *val, int exp);

#endif // !ENV_H