#include "ast.h"

int main(void)
{
	printf("==== Matrix Debug Test ====\n");

	// Define original matrix
	char *words[] = {"hello", "world", "matrix", "copy", NULL};
	printf("\nOriginal matrix address: %p\n", (void *)words);
	for (int i = 0; words[i]; i++)
	{
		printf("words[%d] @ %p = \"%s\"\n", i, (void *)words[i], words[i]);
	}

	// Count elements
	size_t count = mtx_count((void **)words);
	printf("\nCount of original matrix: %zu\n", count);

	// Deep copy
	printf("\nStarting deep copy of matrix...\n");
	char **copy = (char **)mtxdup_n((void **)words, count, ft_strdup, free);

	if (!copy)
	{
		printf("ERROR: mtxdup_n returned NULL.\n");
		return 1;
	}

	// Print copied matrix
	printf("\nCopied matrix address: %p\n", (void *)copy);
	print_string_matrix(copy);

	// Free copied matrix
	printf("\nFreeing copied matrix...\n");
	mtxfree_n((void **)copy, count, free);
	printf("Freeing matrix pointer itself: %p\n", (void *)copy);
	copy = NULL;

	printf("\nFinal state after freeing copy:\n");
	printf("copy = %p\n", (void *)copy);

	printf("\n==== End of Test ====\n");
	return 0;
}
