#ifndef MATRIX_HELPERS_H
# define MATRIX_HELPERS_H

// the place where are the matrix utils (temporarily ast.h for easy debug)
# include "ast.h"

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