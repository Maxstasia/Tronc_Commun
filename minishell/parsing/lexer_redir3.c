#include "../include/minishell.h"

char	*handle_single_redirects(char *current, int *i)
{
	if (current[*i] == '<' && current[*i + 1] && current[*i + 1] != '<'
		&& current[*i + 1] != ' ' && current[*i + 1] != '\t')
	{
		return (redir_in_case(current, i));
	}
	else if (current[*i] == '>' && current[*i + 1] && current[*i + 1] != '>'
		&& current[*i + 1] != ' ' && current[*i + 1] != '\t')
	{
		return (redir_out_case(current, i));
	}
	return (NULL);
}

char	*handle_double_redirects(char *current, int *i)
{
	if (current[*i] == '<' && current[*i + 1] == '<'
		&& current[*i + 2] && current[*i + 2] != ' '
		&& current[*i + 2] != '\t')
	{
		return (heredoc_case(current, i));
	}
	else if (current[*i] == '>' && current[*i + 1] == '>'
		&& current[*i + 2] && current[*i + 2] != ' '
		&& current[*i + 2] != '\t')
	{
		return (append_case(current, i));
	}
	return (NULL);
}

void	skip_redirects(char *current, int *i)
{
	if (current[*i] == '<' && current[*i + 1] == '<')
		(*i) += 2;
	else if (current[*i] == '>' && current[*i + 1] == '>')
		(*i) += 2;
	else if (current[*i] == '<' || current[*i] == '>')
		(*i) += 1;
	else
		(*i) += 1;
}
