/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:17:54 by mstasiak          #+#    #+#             */
/*   Updated: 2024/12/09 18:20:17 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// join and free
char	*ft_join_and_free(char *buffer_static, char *buffer_temp)
{
	char	*temp;

	temp = ft_strjoin(buffer_static, buffer_temp);
	free(buffer_static);
	return (temp);
}

// delete line find
char	*ft_next(char *buffer_static)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	while (buffer_static[i] && buffer_static[i] != '\n')
		i++;
	if (!buffer_static[i])
		return (free(buffer_static), NULL);
	line = ft_calloc((ft_strlen(buffer_static) - i + 1), sizeof(char));
	if (!line)
		return (free(line), free(buffer_static), NULL);
	i++;
	j = 0;
	while (buffer_static[i])
		line[j++] = buffer_static[i++];
	free(buffer_static);
	return (line);
}

// take line for return
char	*ft_line(char *buffer_static)
{
	char	*line;
	int		i;

	i = 0;
	if (!buffer_static[i])
		return (free(buffer_static), NULL);
	while (buffer_static[i] && buffer_static[i] != '\n')
		i++;
	line = ft_calloc(sizeof(char), i + 2);
	if (!line)
		return (free(line), free(buffer_static), NULL);
	i = 0;
	while (buffer_static[i] && buffer_static[i] != '\n')
	{
		line[i] = buffer_static[i];
		i++;
	}
	if (buffer_static[i] && buffer_static[i] == '\n')
		line[i++] = '\n';
	return (line);
}

char	*read_file(int fd, char *buffer_static)
{
	char	*buffer_temp;
	ssize_t	byte_read;

	if (!buffer_static)
	{
		buffer_static = ft_calloc(1, 1);
		if (!buffer_static)
			return (NULL);
	}
	buffer_temp = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer_temp)
		return (free(buffer_temp), free(buffer_static), NULL);
	byte_read = 1;
	while (byte_read > 0)
	{
		byte_read = read(fd, buffer_temp, BUFFER_SIZE);
		if (byte_read == -1)
			return (free(buffer_temp), free(buffer_static), NULL);
		buffer_temp[byte_read] = '\0';
		buffer_static = ft_join_and_free(buffer_static, buffer_temp);
		if (ft_strchr(buffer_temp, '\n'))
			break ;
	}
	free(buffer_temp);
	return (buffer_static);
}

char	*get_next_line(int fd)
{
	static char	*buffer_static;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (free(buffer_static), NULL);
	buffer_static = read_file(fd, buffer_static);
	if (!buffer_static)
		return (NULL);
	line = ft_line(buffer_static);
	if (!line)
		return (NULL);
	buffer_static = ft_next(buffer_static);
	return (line);
}
