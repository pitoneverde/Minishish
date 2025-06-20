int	ft_isupper(int c);

int	ft_isupper(int c)
{
	if (c >= 0x41 && c <= 0x5A)
		return (c);
	return (0);
}
