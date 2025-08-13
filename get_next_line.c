/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 12:26:37 by lbento            #+#    #+#             */
/*   Updated: 2025/08/13 20:12:38 by lbento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char		*get_next_line(int fd);
static char	*read_line(int fd, char *buffer);
static char	*fill_line(char *remainder);

char	*get_next_line(int fd)
{
	char		*line;
	static char	*remainder;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
// if (remainder == NULL)
// 	remainder = ft_strjoin(remainder, "");
	if (ft_strlen(remainder) == 0)
	{
		free(remainder);
		remainder = NULL;
		return (NULL);
	}
	remainder = read_line(fd, remainder);
	if (!remainder)
		return (NULL);
	line = fill_line(remainder);
	return (line);
}

static char	*read_line(int fd, char *remainder)
{
	char	*buffer;
	int		bytes_read;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!remainder)
		remainder = malloc(1);
	bytes_read = 1;
	while (bytes_read > 0 && ft_strchr(remainder, '\n') == NULL)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(remainder);
			free(buffer);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		remainder = ft_strjoin(remainder, buffer);
		free(remainder);
	}
	free(buffer);
	if (bytes_read < 0)
		return (NULL);
	return (remainder);
}

static char	*fill_line(char	*str)
{
	int		len;
	int		i;
	char	*line;

	len = 0;
	i = 0;
	if (!str || !str[i])
		return (NULL);
	while (str[len] && str[len] != '\n')
		len++;
	line = (char *)malloc(len + 2 * sizeof(char));
	if (!line)
		return (NULL);
	while (str[i] && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		line[i++] = '\n';
	line[i++] = '\0';
	return (line);
}


#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("test.txt", O_RDONLY);
	line = get_next_line(fd);
	// while (line)
	// {
		printf("%s", line);
		free(line);
	// }
	close(fd);
	return (0);
}

//cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c