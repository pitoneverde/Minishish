#include "libft.h"

int ft_strcmp(const char *s1, const char *s2)
{
	return ft_strncmp(s1, s2, (size_t)-1);
}