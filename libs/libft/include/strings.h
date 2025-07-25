#if !defined(STRINGS_H)
# define STRINGS_H
# include <stdlib.h>

int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_striteri(const char *s, void (*f)(unsigned int, char *));
char	*ft_strdup(const char *s);
char	*ft_strchr(const char *string, int c);
char	*ft_strrchr(const char *string, int c);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_strtrim(const char *s1, const char *set);
char	*ft_substr(const char *s, unsigned int start, size_t len);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strmapi(char *s, char (*f)(unsigned int, char));
char	**ft_split(const char *s, char c);
size_t	ft_strlen(const char *__s);
size_t	ft_strlcat(char *to, const char *from, size_t size);
size_t	ft_strlcpy(char *to, const char *from, size_t size);

#endif // STRINGS_H
