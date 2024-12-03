/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main(get_next_line).c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 08:44:02 by mstasiak          #+#    #+#             */
/*   Updated: 2024/12/03 10:23:37 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("get_next_line_utils.c", O_RDONLY);
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	/* char *s = get_next_line(fd);
	printf("%s", s);
	free(s); */
	close(fd);
	return (0);
}
