#include "minishell.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void print_env(t_list *env);
void print_envp(char **envp);

int main(int argc, char **argv, char **envp)
{
	t_list *env;
	char **dup_envp;
	char *val;
	// char *long_key;
	// char *long_value;

	(void)argc;
	(void)argv;

	printf("=== Edge Case Tests for minishell env handling ===\n");

	// Initialize env list
	env = envp_to_env(envp);

	// --- 1. Empty key or value ---
	printf("\n--- Test 1: Empty key and empty value ---\n");
	set_env_var(&env, "", "some_value", 1);
	set_env_var(&env, "EMPTY_VAL", "", 1);
	print_env(env);
	val = get_env_value(env, "");
	printf("Get empty key value: %s\n", val ? val : "(not found)");
	unset_env_var(&env, "");
	printf("After unsetting empty key:\n");
	print_env(env);

	// --- 2. Very long key and value ---
	// printf("\n--- Test 2: Very long key and value ---\n");
	// long_key = malloc(10001);
	// long_value = malloc(10001);
	// if (!long_key || !long_value)
	// {
	// 	fprintf(stderr, "Failed to allocate memory for long key/value\n");
	// 	free(long_key);
	// 	free(long_value);
	// 	free_env(env);
	// 	return (1);
	// }
	// memset(long_key, 'K', 10000);
	// long_key[10000] = '\0';
	// memset(long_value, 'V', 10000);
	// long_value[10000] = '\0';

	// set_env_var(&env, long_key, long_value, 1);
	// val = get_env_value(env, long_key);
	// printf("Length of long key value: %zu\n", val ? strlen(val) : 0);

	// free(long_key);
	// free(long_value);

	// --- 3. Special characters in key and value ---
	printf("\n--- Test 3: Special characters in key and value ---\n");
	set_env_var(&env, "MY=VAR", "value=with=equals", 1);
	set_env_var(&env, "VAR NAME", "value with spaces", 1);
	set_env_var(&env, "VAR\nNAME", "value with newline\ninside", 1);
	print_env(env);

	val = get_env_value(env, "MY=VAR");
	printf("MY=VAR = %s\n", val ? val : "(not found)");
	val = get_env_value(env, "VAR NAME");
	printf("VAR NAME = %s\n", val ? val : "(not found)");
	val = get_env_value(env, "VAR\nNAME");
	printf("VAR\\nNAME = %s\n", val ? val : "(not found)");

	// --- 4. Duplicate keys on initialization ---
	printf("\n--- Test 4: Duplicate keys in envp ---\n");
	char *dup_envp_init[] = {
		"PATH=/bin",
		"PATH=/usr/bin",
		NULL};
	t_list *dup_env = envp_to_env(dup_envp_init);
	print_env(dup_env);
	val = get_env_value(dup_env, "PATH");
	printf("PATH value after duplicates: %s\n", val ? val : "(not found)");
	free_env(dup_env);

	// --- 5. Unsetting a variable that doesn't exist ---
	printf("\n--- Test 5: Unset non-existent variable ---\n");
	unset_env_var(&env, "THIS_DOES_NOT_EXIST");
	print_env(env);

	// --- 6. Overwrite exported and non-exported ---
	printf("\n--- Test 6: Overwrite exported / non-exported ---\n");
	set_env_var(&env, "TEST_VAR", "initial", 0);
	print_env(env);
	set_env_var(&env, "TEST_VAR", "exported_now", 1);
	print_env(env);
	set_env_var(&env, "TEST_VAR", "non_exported_now", 0);
	print_env(env);

	// --- 7. NULL pointers ---
	printf("\n--- Test 7: NULL pointer handling ---\n");
	val = get_env_value(NULL, "PATH");
	printf("Get env value with NULL env: %s\n", val ? val : "(null or not found)");
	val = get_env_value(env, NULL);
	printf("Get env value with NULL key: %s\n", val ? val : "(null or not found)");

	set_env_var(NULL, "VAR", "value", 1);
	set_env_var(&env, NULL, "value", 1);
	set_env_var(&env, "VAR", NULL, 1);

	unset_env_var(NULL, "VAR");
	unset_env_var(&env, NULL);

	// --- 8. Convert empty env list to envp ---
	printf("\n--- Test 8: Empty env list to envp ---\n");
	t_list *empty_env = NULL;
	char **empty_envp = env_to_envp(empty_env);
	print_envp(empty_envp);
	mtxfree_str(empty_envp);

	// Cleanup
	dup_envp = env_to_envp(env);
	printf("\nFinal exported envp matrix:\n");
	print_envp(dup_envp);

	mtxfree_str(dup_envp);
	free_env(env);

	return (0);
}

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