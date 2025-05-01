#include "../includes/minishell.h"

int	ft_isspecial(char c)
{
	if (c == '|' || c == '<' || c == '>' || c == ';' || c == '&')
		return (1);
	return (0);
}

int ft_isoperator(char c)
{
	if (c == '-' || c == '+' || c == '*' || c == '/' || c == '%')
		return (1);
	return (0);
}