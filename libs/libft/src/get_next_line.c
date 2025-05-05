/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 04:17:32 by plichota          #+#    #+#             */
/*   Updated: 2025/02/03 18:42:20 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

ssize_t	ft_strlen_line(char *buff)
{
	ssize_t	i;

	i = 0;
	if (!buff)
		return (-1);
	while (i < BUFFER_SIZE && buff[i])
	{
		if ((char)buff[i] == '\n')
			return (i + 1);
		i++;
	}
	return (i);
}

char	*append_line(char *buff, char **res)
{
	ssize_t	line_size;
	size_t	res_size;
	char	*temp;

	res_size = 0;
	if (!buff)
		return (NULL);
	line_size = ft_strlen_line(buff);
	if (*res)
		res_size = ft_strlen(*res);
	temp = ft_calloc(line_size + res_size + 1, 1);
	if (!temp)
		return (NULL);
	if (res_size > 0)
		ft_memcpy(temp, *res, res_size);
	if (line_size > 0)
		ft_memcpy(&temp[res_size], buff, line_size);
	temp[res_size + line_size] = '\0';
	free(*res);
	*res = temp;
	ft_memcpy(buff, &buff[line_size], BUFFER_SIZE - line_size + 1);
	return (*res);
}

int	index_of(char c, char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (-1);
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1] = {0};
	char		*res;
	ssize_t		nbytes;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	res = NULL;
	while (!res || ft_strchr(res, '\n') == NULL)
	{
		while (ft_strlen(buffer) > 0)
		{
			append_line(buffer, &res);
			if (res != NULL && ft_strchr(res, '\n') != NULL)
				return (res);
		}
		nbytes = read(fd, buffer, BUFFER_SIZE);
		if (nbytes == 0)
			return (res);
		if (nbytes < 0)
			return (NULL);
		buffer[nbytes] = '\0';
	}
	return (res);
}

/*
int	main(int argc, char *argv[])
{
	// cc get_next_line.c get_next_line_utils.c get_next_line.h 
	//-Wall -Werror -Wextra -D BUFFER_SIZE=10
	// valgrind --leak-check=full --show-leak-kinds=all --quiet ./a.out
	char	*path;
	char	*line;
	int	fd;
	// (void)argc;
	// (void)argv;
	if (argc > 1) {
		path = argv[1];
	} else {
		path = "text0.txt";
	}

	// fd = 0;
	fd = open(path, O_RDONLY);
	// if (fd == -1)
	// {
	// 	write(1, "Errore nell'apertura del file\n", 30);
	// 	return (1);
	// }

	line = get_next_line(fd);
	// line = get_next_line(-1);
	// line = get_next_line(0);
	while(line) {
		printf(">>LINE: %s", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}
*/
