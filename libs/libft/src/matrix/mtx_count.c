#include "matrix.h"

// NULL-terminated matrix only
size_t mtx_count(void **matrix)
{
	size_t n;

	n = 0;
	while (matrix && matrix[n])
		n++;
	return (n);
}
