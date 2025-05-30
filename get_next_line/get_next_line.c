/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:17:54 by mstasiak          #+#    #+#             */
/*   Updated: 2025/05/26 15:06:57 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_join_and_free(char *buffer_static, char *buffer_temp)
{
	char	*temp;

	if (!buffer_temp)
		return (free(buffer_static), NULL);
	else if (!buffer_static)
		return (NULL);
	temp = ft_strjoin(buffer_static, buffer_temp);
	if (!temp)
		return (free(buffer_static), NULL);
	return (free(buffer_static), temp);
}

// suprimer la derniere ligne utilisee
char	*ft_next(char *buffer_static)
{
	int		i;
	int		j;
	char	*line;

	if (!buffer_static)
		return (NULL);
	i = 0;
	while (buffer_static[i] && buffer_static[i] != '\n')
		i++;
	if (!buffer_static[i])
		return (free(buffer_static), NULL);
	line = ft_calloc((ft_strlen(buffer_static) - i + 1), sizeof(char));
	if (!line)
		return (free(buffer_static), NULL);
	i++;
	j = 0;
	while (buffer_static[i])
		line[j++] = buffer_static[i++];
	return (free(buffer_static), line);
}

// prends une ligne afin de la retourner
char	*ft_line(char *buffer_static)
{
	char	*line;
	int		i;

	i = 0;
	if (!buffer_static[i])
		return (NULL);
	while (buffer_static[i] && buffer_static[i] != '\n')
		i++;
	line = ft_calloc(sizeof(char), i + 2);
	if (!line)
		return (free(line), free(buffer_static), NULL);
	i = -1;
	while (i++, buffer_static[i] && buffer_static[i] != '\n')
		line[i] = buffer_static[i];
	if (buffer_static[i] && buffer_static[i] == '\n')
		line[i++] = '\n';
	return (line);
}

char	*read_file(int fd, char *buffer_static, ssize_t byte_read)
{
	char	*buffer_temp;

	if (!buffer_static)
	{
		buffer_static = ft_calloc(1, 1);
		if (!buffer_static)
			return (NULL);
	}
	buffer_temp = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer_temp)
		return (NULL);
	while (byte_read > 0)
	{
		byte_read = read(fd, buffer_temp, BUFFER_SIZE);
		if (byte_read == -1 && !buffer_static)
			return (free(buffer_temp), NULL);
		buffer_temp[byte_read] = '\0';
		buffer_static = ft_join_and_free(buffer_static, buffer_temp);
		if (!buffer_static)
			return (free(buffer_temp), NULL);
		if (ft_strchr(buffer_temp, '\n'))
			break ;
	}
	return (free(buffer_temp), buffer_static);
}

char	*get_next_line(int fd)
{
	static char	*buffer_static;
	char		*line;
	ssize_t		byte_read;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (free(buffer_static), buffer_static = NULL, NULL);
	byte_read = 1;
	buffer_static = read_file(fd, buffer_static, byte_read);
	if (!buffer_static || !buffer_static[0])
		return (free(buffer_static), buffer_static = NULL, NULL);
	line = ft_line(buffer_static);
	if (!line)
		return (free(buffer_static), buffer_static = NULL, NULL);
	buffer_static = ft_next(buffer_static);
	return (line);
}
