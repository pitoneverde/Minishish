#include "matrix.h"

// NULL-terminated matrix only
void **mtxdup(void **mtx, void *(c)(void *), void(f)(void *))
{
	size_t dim;

	if (!mtx)
		return (NULL);
	dim = mtx_count(mtx);
	return (mtxdup_n(mtx, dim, c, f));
}