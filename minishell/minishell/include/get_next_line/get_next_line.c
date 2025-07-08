/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:04:45 by mstasiak          #+#    #+#             */
/*   Updated: 2025/03/31 15:40:52 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*extract_line(char **remainder)
{
	char	*line;
	char	*tmp;
	int		i;

	if (!*remainder || !**remainder)
		return (free(*remainder), *remainder = NULL, NULL);
	i = 0;
	while ((*remainder)[i] && (*remainder)[i] != '\n')
		i++;
	line = (char *)malloc(i + ((*remainder)[i] == '\n') + 1);
	if (!line)
		return (free(*remainder), *remainder = NULL, NULL);
	i = -1;
	while ((*remainder)[++i] && (*remainder)[i] != '\n')
		line[i] = (*remainder)[i];
	if ((*remainder)[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	if (!(*remainder)[i])
		return (free(*remainder), *remainder = NULL, line);
	tmp = ft_strjoin_gnl(NULL, *remainder + i);
	if (!tmp)
		return (free(*remainder), free(line), *remainder = NULL, NULL);
	return (free(*remainder), *remainder = tmp, line);
}

static char	*read_fd(int fd, char *remainder)
{
	char	*buffer;
	int		bytes_read;

	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (free(remainder), NULL);
	bytes_read = 1;
	while (bytes_read > 0 && (!remainder || !ft_strchr_gnl(remainder, '\n')))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(buffer), free(remainder), NULL);
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		remainder = ft_strjoin_gnl(remainder, buffer);
		if (!remainder)
			return (free(buffer), NULL);
	}
	free(buffer);
	return (remainder);
}

char	*get_next_line(int fd)
{
	static char	*remainder;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	remainder = read_fd(fd, remainder);
	if (!remainder)
		return (NULL);
	line = extract_line(&remainder);
	return (line);
}
