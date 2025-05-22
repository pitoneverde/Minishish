#ifndef MATRIX_H
# define MATRIX_H

// Core low-level matrix utilities
size_t mtx_count(void **matrix);
void mtxfree(void **mtx, void(f)(void *));
void mtxfree_n(void **mtx, size_t dim, void (*f)(void *));
void **mtxdup(void **mtx, void *(c)(void *), void(f)(void *));
void **mtxdup_n(void **mtx, size_t dim, void *(c)(void *), void(f)(void *));

// void *ft_realloc(void *p);
// # define LIST_TO_ARRAY_AS(type, lst, dim_ptr)
// 	((type **)lst_to_array_n((lst), (dim_ptr)));

// wrappers for project specific matrix handling
void *copy_string(void *ptr);
void print_string_matrix(char **matrix);
void free_string(void *row);

// TODO: Replace free_string with free once debugged (or keep a debug version commented)
static inline char **mtxdup_str(char **matrix)
{
	return ((char **)mtxdup((void **)matrix, copy_string, free_string));
}

// TODO: Replace free_string with free once debugged (or keep a debug version commented)
static inline void mtxfree_str(char **matrix)
{
	mtxfree((void **)matrix, free_string);
}

#endif // !MATRIX_HELPERS_H