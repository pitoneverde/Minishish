int ft_islower(int c);

int	ft_islower(int c)
{
	if (c >= 0x61 && c <= 0x7A)
		return (c);
	return (0);
}
