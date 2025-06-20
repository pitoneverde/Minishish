#include <stdio.h>
#include "strbuilder.h"

int main(void)
{
	t_sb *sb;

	printf("=== strbuilder edge cases ===\n");

	// Test: Empty builder
	sb = sb_create(0);
	printf("[empty create] len = %zu, cap = %zu\n", sb_length(sb), sb_capacity(sb));

	// Test: Append empty string
	sb_append_str(sb, "");
	printf("[append empty] len = %zu\n", sb_length(sb));

	// Test: Append NULL (should do nothing or fail safely)
	sb_append_str(sb, NULL);
	sb_append_n(sb, NULL, 0);
	printf("[append NULLs] len = %zu\n", sb_length(sb));

	// Test: Append large string
	for (int i = 0; i < 1000; i++)
		sb_append_char(sb, 'x');
	printf("[append 1000 chars] len = %zu, cap = %zu\n", sb_length(sb), sb_capacity(sb));

	// Test: Clear and reuse
	sb_clear(sb);
	printf("[after clear] len = %zu, cap = %zu\n", sb_length(sb), sb_capacity(sb));
	sb_append_str(sb, "reused");
	char *res = sb_build(sb);
	printf("[after reuse] result = [%s]\n", res);
	free(res);

	// Freeing NULL-safe
	sb_free(NULL);
	sb_free(sb);

	return 0;
}
