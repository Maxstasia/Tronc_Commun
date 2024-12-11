/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main(get_next_line).c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 08:44:02 by mstasiak          #+#    #+#             */
/*   Updated: 2024/12/11 16:00:35 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int		fd;

	//fd = open("~/francinette/tests/get_next_line/fsoares/lines_around_10.txt", O_RDWR);
	fd = open("./bible.txt", O_RDWR);
	char	*line;
	//int theend = 0;
	while ((line = get_next_line(0)) != NULL)
	{
		/* if (theend == 1024)
		{
			printf("%s", line);
			free(line);
			break;
		}
		++theend; */
		if (line == NULL)
			printf("line = NULL");
		printf("%s", line);
		free(line);
	}
	/* char *s = get_next_line(fd);
	if (!s)
	{
		close(fd);
		return (0);
	}
	printf("%s", s);
	free(s); */
	if (line == NULL)
		printf("line = NULL");
	close(fd);
	return (0);
}
