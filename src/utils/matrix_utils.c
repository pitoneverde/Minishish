#include "ast.h"

// wrapper for project specific matrix handling
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
