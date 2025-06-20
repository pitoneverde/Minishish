# include "strbuilder.h"

// Clears the builder content (does not free the buffer).
void sb_clear(t_sb *sb)
{
	sb->len = 0;
}
