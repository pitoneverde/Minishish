#include "strbuilder.h"

// Finalizes and returns a malloc’d null-terminated string.
// Frees the builder internally.
char	*sb_build(t_sb *sb)
{
	char	*result;

	if (!sb_ensure_capacity(sb, sb->len + 1))
	{
		sb_free(sb);
		return (NULL);
	}
	sb->buf[sb->len] = '\0';
	result = ft_strdup(sb->buf);
	return (result);
}
