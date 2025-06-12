#include "minishell.h"

// Helper function to print t_env list
void print_env(t_list *env)
{
	t_env *entry;

	printf("Environment Variables:\n");
	while (env)
	{
		entry = env->content;
		printf(" - %s=%s (exported: %d)\n", entry->key, entry->value, entry->exported);
		env = env->next;
	}
}

// Helper to print char **envp
void print_envp(char **envp)
{
	printf("envp matrix:\n");
	for (size_t i = 0; envp && envp[i]; i++)
		printf(" [%zu] %s\n", i, envp[i]);
}

int main(int argc, char **argv, char **envp)
{
	t_list *env;
	char **dup_envp;
	char *val;

	(void)argc;
	(void)argv;

	printf("HERE\n");
	// Convert envp to list
	env = envp_to_env(envp);
	print_env(env);

	// Test: get a value
	val = get_env_value(env, "PATH");
	printf("\nPATH = %s\n", val ? val : "(not found)");

	// Test: set new variable
	set_env_var(&env, "MY_VAR", "123", 1);
	set_env_var(&env, "PATH", "/custom/path", 1); // overwrite
	printf("\nAfter setting MY_VAR and modifying PATH:\n");
	print_env(env);

	// Test: unset variable
	unset_env_var(&env, "OLDPWD");
	printf("\nAfter unsetting OLDPWD:\n");
	print_env(env);

	// Test: convert back to envp
	dup_envp = env_to_envp(env);
	printf("\nExported envp matrix:\n");
	print_envp(dup_envp);

	// Cleanup
	mtxfree_str(dup_envp);
	free_env(env);
	return (0);
}
