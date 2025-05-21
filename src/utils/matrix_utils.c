#include "ast.h"

// ---------- TODO: MOVE INTO LIBFT -----------

// frees a matrix of any type (given dim)
// 'f' is to free one row
void mtxfree_n(void **matrix, size_t dim, void (*f)(void *))
{
	size_t	i;

	if (!matrix || !f)
		return;
	i = 0;
	while (i < dim && matrix[i])
		f(matrix[i++]);
	free(matrix);
	matrix = NULL;
}

// copies a matrix of any type (given dim)
// 'c' is to copy one row
// 'f' is to free one row
void **mtxdup_n(void **mtx, size_t dim, void *(c)(void *), void(f)(void *))
{
	size_t i;
	void **copy;

	if (!mtx || !c)
		return (NULL);
	copy = malloc(sizeof(void *) * (dim + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < dim)
	{
		copy[i] = c(mtx[i]);
		if (!copy[i])
			return (mtxfree_n(copy, i, f), NULL);
		i++;
	}
	copy[dim] = NULL;
	return (copy);
}

// NULL-terminated matrix only
size_t mtx_count(void **matrix)
{
	size_t n;

	n = 0;
	while (matrix && matrix[n])
		n++;
	return (n);
}

// NULL-terminated matrix only
void **mtxdup(void **mtx, void *(c)(void *), void (f)(void *))
{
	size_t dim;

	if (!mtx)
		return (NULL);
	dim = mtx_count(mtx);
	return (mtxdup_n(mtx, dim, c, f));
}

// NULL-terminated matrix only
void mtxfree(void ** mtx, void (f)(void *))
{
	size_t dim;

	if (!mtx)
		return ;
	dim = mtx_count(mtx);
	return (mtxfree_n(mtx, dim, f));
}

// ---------- END OF LIBFT FUNCTIONS -----------

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
