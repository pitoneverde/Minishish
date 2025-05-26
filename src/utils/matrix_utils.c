#include "ast.h"

void *copy_string(void *ptr)
{
	if (!ptr)
		return (NULL);
	return (ft_strdup((char *)ptr));
}

void print_string_matrix(char **matrix)
{
	if (!matrix)
	{
		printf("(null matrix)\n");
		return;
	}
	for (size_t i = 0; matrix[i]; i++)
	{
		printf("[%zu]: \"%s\"\n", i, matrix[i]);
	}
}

void free_string(void *row)
{
	// printf("Freeing string at %p: \"%s\"\n", row, (char *)row);
	free(row);
}
