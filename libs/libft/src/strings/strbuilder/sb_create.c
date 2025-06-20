# include "strbuilder.h"

// Creates a new string builder with an initial capacity.
t_strbuilder	*sb_create(size_t initial_capacity)
{
	t_strbuilder *sb;

	sb = malloc(sizeof(t_strbuilder));
	if (!sb)
		return (NULL);
	sb->buf = malloc(initial_capacity);
	if (!sb->buf)
		return (free(sb), NULL);
	sb->cap = initial_capacity;
	sb->len = 0;
	sb->buf[0] = '\0';
	return (sb);
}