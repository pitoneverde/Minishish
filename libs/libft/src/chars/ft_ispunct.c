#include "chars.h"

int	ft_ispunct(int c);

int	ft_ispunct(int c)
{
	if (c >= 0x21 && c <= 0x7E && !ft_isalnum(c))
		return (c);
	return (0);
}