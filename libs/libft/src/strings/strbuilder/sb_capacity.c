#include "strbuilder.h"

// Returns the current capacity of the buffer.
size_t sb_capacity(t_sb *sb)
{
	return (sb->cap);
}
