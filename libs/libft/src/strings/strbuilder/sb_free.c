#include "strbuilder.h"

// Frees the builder and its buffer without returning a string.
void sb_free(t_sb *sb)
{
	if (!sb)
		return ;
	if (sb->buf)
		free(sb->buf);
	free(sb);
}
