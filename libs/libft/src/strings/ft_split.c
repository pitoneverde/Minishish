/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 22:40:27 by sabruma           #+#    #+#             */
/*   Updated: 2024/11/29 22:40:29 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char			**ft_split(const char *s, char c);
static int		count(const char *s, char c);
static char		*split(const char *c_s, char c);
static int		split_helper(const char **s, char c, char **mx, int *i);

char	**ft_split(const char *s, char c)
{
	int			i;
	char		**mx;

	mx = (char **)malloc((count(s, c) + 1) * sizeof(char *));
	if (mx == NULL)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (!split_helper(&s, c, mx, &i))
			return (NULL);
	}
	mx[i] = NULL;
	return (mx);
}

static int	split_helper(const char **s, char c, char **mx, int *i)
{
	if (*s && **s)
	{
		mx[*i] = split(*s, c);
		if (!mx[*i])
		{
			while (*i)
				free(mx[--(*i)]);
			free(mx);
			return (0);
		}
		*s += ft_strlen(mx[*i]);
		(*i)++;
	}
	return (1);
}

static char	*split(const char *c_s, char c)
{
	int		len;
	char	*p;
	int		idx;

	len = 0;
	while (c_s[len] != '\0' && c_s[len] != c)
		len++;
	p = (char *)malloc(len + 1);
	if (!p)
		return (NULL);
	idx = 0;
	while (idx < len)
	{
		p[idx] = c_s[idx];
		idx++;
	}
	p[idx] = '\0';
	return (p);
}

static int	count(const char *s, char c)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
		{
			n++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
	}
	return (n);
}
