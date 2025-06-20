#include "strbuilder.h"

// Appends a null-terminated string to the builder.
void sb_append_str(t_sb *sb, const char *str)
{
	if (!str)
		return ;
	sb_append_n(sb, str, ft_strlen(str));
}
