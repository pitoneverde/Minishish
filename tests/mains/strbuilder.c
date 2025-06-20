#include <stdio.h>
#include "strbuilder.h"

int main(void)
{
	t_sb *sb;

	printf("=== strbuilder tests ===\n");

	sb = sb_create(8);
	if (!sb)
	{
		fprintf(stderr, "Failed to allocate sb\n");
		return (1);
	}

	printf("Initial cap: %zu\n", sb_capacity(sb));
	printf("Initial len: %zu\n", sb_length(sb));

	sb_append_str(sb, "Hello");
	sb_append_char(sb, ',');
	sb_append_char(sb, ' ');
	sb_append_str(sb, "world");

	char *raw = "!";
	sb_append_n(sb, raw, 1);

	printf("After appends: len = %zu, cap = %zu\n", sb_length(sb), sb_capacity(sb));

	sb_shrink_to_fit(sb);
	printf("After shrink_to_fit: cap = %zu\n", sb_capacity(sb));

	char *final = sb_build(sb);
	if (!final)
	{
		fprintf(stderr, "Failed to build final string\n");
		return (1);
	}

	printf("Final result: [%s]\n", final);
	free(final);

	return (0);
}
