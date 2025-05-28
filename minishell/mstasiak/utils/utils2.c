#include "../include/minishell.h"

int		get_index(char *str, int i)
{
	while (str[i] && str[i] != ' ' && str[i] != '\t')
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			if (str[i] == '\'')
				i = single_quoted(str, i);
			else if (str[i] == '\"')
				i = double_quoted(str, i);
			if (i == -1)
				return (-1);
			i++;
		}
		else
			i++;
	}
	return (i);
}