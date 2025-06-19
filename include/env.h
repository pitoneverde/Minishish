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

// utils
int		is_valid_var_name(const char *name);
void	*env_to_str(void *ptr);
void	unset_env_var(t_list **env, const char *key);
char	*get_env_value(const t_list *env, const char *key);
void	set_env_var(t_list **env, const char *key, const char *val, int exp);

#endif // !ENV_H