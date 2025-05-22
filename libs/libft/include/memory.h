#if !defined(MEMORY_H)
# define MEMORY_H
# include <stdlib.h>

int		ft_memcmp(const void *a1, const void *a2, size_t size);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nitems, size_t size);
void	*ft_memset(void *block, int c, size_t size);
void	*ft_memchr(const void *block, int c, size_t size);
void	*ft_memcpy(void *to, const void *from, size_t size);
void	*ft_memmove(void *to, const void *from, size_t size);

#endif // MEMORY_H
