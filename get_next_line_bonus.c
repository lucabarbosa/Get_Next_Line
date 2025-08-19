/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 13:47:29 by lbento            #+#    #+#             */
/*   Updated: 2025/08/15 14:06:37 by lbento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd);
char	*read_line(int fd, char *remaining, char *buffer);
char	*save_file(char *line);

char	*get_next_line(int fd)
{
	static char	*remaining[MAX_FD];
	char		*line;
	char		*buffer;
	int			test_read;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	test_read = read(fd, 0, 0);
	if (!buffer)
		return (NULL);
	if (fd < 0 || BUFFER_SIZE <= 0 || test_read < 0)
	{
		free(remaining[fd]);
		free(buffer);
		remaining[fd] = NULL;
		buffer = NULL;
		return (NULL);
	}
	line = read_line(fd, remaining[fd], buffer);
	free(buffer);
	buffer = NULL;
	if (!line)
		return (NULL);
	remaining[fd] = save_file(line);
	return (line);
}

char	*read_line(int fd, char *remaining, char *buffer)
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

char	*save_file(char *line)
{
	char	*rest;
	size_t	i;
	size_t	size_line;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	if (line[i] == '\0')
	{
		return (NULL);
	}
	size_line = (ft_strlen(line) - i);
	rest = ft_substr(line, i + 1, size_line);
	if (*rest == '\0')
	{
		free(rest);
		rest = NULL;
	}
	line[i + 1] = '\0';
	return (rest);
}

// #include<stdio.h>
// #include<fcntl.h>

// int	main(void)
// {
// 	int	fd[2];
// 	char	*result;

// 	fd[0] = open("test.txt", O_RDONLY);
// 	fd[1] = open("test2.txt", O_RDONLY);

// 	result = get_next_line(fd[0]);
// 	printf("%s", result);
// 	result = get_next_line(fd[1]);
// 	printf("%s", result);
// 	result = get_next_line(fd[0]);
// 	printf("%s", result);
// 	result = get_next_line(fd[1]);
// 	printf("%s", result);
// 	result = get_next_line(fd[0]);
// 	printf("%s", result);
// 	result = get_next_line(fd[1]);
// 	printf("%s", result);

// 	close(fd[0]);
// 	close(fd[1]);
// 	return (0);
// }
