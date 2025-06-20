#ifndef STRBUILDER_H
# define STRBUILDER_H

# include <stdlib.h>

typedef struct s_strbuilder
{
	char	*buf;	// Internal buffer
	size_t	len;	// Current length of the string
	size_t	cap;	// Allocated buffer size
}	t_strbuilder;

t_strbuilder *sb_create(size_t initial_capacity);

// Appends a null-terminated string to the builder.
void sb_append_str(t_strbuilder *sb, const char *str);

// Appends a single character to the builder.
void sb_append_char(t_strbuilder *sb, char c);

// Appends `n` bytes from a buffer (not necessarily null-terminated).
void sb_append_n(t_strbuilder *sb, const char *data, size_t n);

// Clears the builder content (does not free the buffer).
void sb_clear(t_strbuilder *sb);

// Shrinks the internal buffer to fit the current string exactly.
void sb_shrink_to_fit(t_strbuilder *sb);

// Returns the current length of the string.
size_t sb_length(t_strbuilder *sb);

// Returns the current capacity of the buffer.
size_t sb_capacity(t_strbuilder *sb);

// Finalizes and returns a malloc’d null-terminated string.
// Frees the builder internally.
char *sb_build(t_strbuilder *sb);

// Frees the builder and its buffer without returning a string.
void sb_free(t_strbuilder *sb);

#endif
