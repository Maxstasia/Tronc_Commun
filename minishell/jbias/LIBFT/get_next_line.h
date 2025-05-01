/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbias <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 11:37:53 by jbias             #+#    #+#             */
/*   Updated: 2025/01/21 15:34:04 by jbias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stddef.h>
# include <string.h>

# define BUFFER_SIZE 1

char	*get_next_line(int fd);
char	*ft_strjoinn(char *s1, char *s2);
int		ft_strchrr(char *str, char c);
int		ft_strlenn(char	*str);
void	*ft_callocc(int nmemb, int size);

#endif
