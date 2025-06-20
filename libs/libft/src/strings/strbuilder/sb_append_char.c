#include "strbuilder.h"

// Appends a single character to the builder.
void sb_append_char(t_sb *sb, char c)
{
	if (!sb_ensure_capacity(sb, sb->len + 1))
		return ;
	sb->buf[sb->len++] = c;
}