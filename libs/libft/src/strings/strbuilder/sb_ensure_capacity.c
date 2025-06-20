# include "strbuilder.h"

// Internal helper that reallocs the buffer if needed.
int	sb_ensure_capacity(t_sb *sb, size_t required)
{
	size_t	new_cap;
	char	*new_buf;

	if (required <= sb->cap)
		return (1);
	if (sb->cap > 0)
		new_cap = sb->cap;
	else
		new_cap = 16;
	while (new_cap < required)
		new_cap *= GROWTH_FACTOR;
	new_buf = ft_realloc(sb->buf, sb->cap, new_cap);
	if (!new_buf)
		return (0);
	sb->buf = new_buf;
	sb->cap = new_cap;
	return (1);
}
