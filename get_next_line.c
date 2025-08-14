/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 10:51:16 by lbento            #+#    #+#             */
/*   Updated: 2025/08/14 20:23:35 by lbento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char			*get_next_line(int fd);
static char		*read_line(int fd, char *left_c, char *buffer);
static char		*save_file(char *line);

char	*get_next_line(int fd)
{
	static char	*remaining;
	char		*line;
	char		*buffer;
	int			test_read;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	test_read = read(fd, 0, 0);
	if (!buffer)
		return (NULL);
	if (fd < 0 || BUFFER_SIZE <= 0 || test_read < 0)
	{
		free(remaining);
		free(buffer);
		remaining = NULL;
		buffer = NULL;
		return (NULL);
	}
	line = read_line(fd, remaining, buffer);
	free(buffer);
	buffer = NULL;
	if (!line)
		return (NULL);
	remaining = save_file(line);
	return (line);
}

static char	*read_line(int fd, char *remaining, char *buffer)
{
	int		bytes_read;
	char	*temp;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(remaining);
			return (NULL);
		}
		else if (bytes_read == 0)
			return (remaining);
		buffer[bytes_read] = '\0';
		if (!remaining)
			remaining = ft_strdup("");
		temp = remaining;
		remaining = ft_strjoin(temp, buffer);
		free(temp);
		temp = NULL;
		if (ft_strchr(buffer, '\n'))
			return (remaining);
	}
	return (remaining);
}

static char	*save_file(char *line)
{
	char	*rest;
	size_t	i;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	if (line[i] == '\0')
	{
		return (NULL);
	}
	rest = ft_substr(line, i + 1, ft_strlen(line) - i);
	if (*rest == '\0')
	{
		free(rest);
		rest = NULL;
	}
	line[i + 1] = '\0';
	return (rest);
}

// #include <fcntl.h>
// #include <stdio.h>

// int	main(void)
// {
// 	int		fd;
// 	char	*line;

// 	fd = open("test.txt", O_RDONLY);
// 	line = get_next_line(fd);
// 	if(!line)
// 	printf("Vindo nulo");
// 	while (line)
// 	{
// 		printf("%s", line);
// 		free(line);
// 		line = get_next_line(fd);
// 	}
// 	close(fd);
// 	return (0);
// }