#include "matrix.h"

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
