/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:53:33 by mstasiak          #+#    #+#             */
/*   Updated: 2025/06/11 16:52:52 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	has_file_after_redirection(const char *input, const char *redir)
{
    char *pos = ft_strstr(input, redir);
    if (!pos)
        return (1); // Pas de redirection trouvée
    
    pos += ft_strlen(redir);
    
    // Ignorer les espaces
    while (*pos && (*pos == ' ' || *pos == '\t'))
        pos++;
    
    // Vérifier qu'il y a quelque chose après
    if (!*pos || *pos == '|' || *pos == '<' || *pos == '>')
        return (0);
    
    return (1);
}

int validate_redirection_syntax(const char *input)
{
    int i = 0;
    char quote = 0;
    
    while (input[i])
    {
        if (input[i] == '\'' || input[i] == '\"')
        {
            if (!quote)
                quote = input[i];
            else if (quote == input[i])
                quote = 0;
        }
        else if (!quote)
        {
            // Vérifier les redirections
            if (input[i] == '<' || input[i] == '>')
            {
                // Compter les caractères de redirection
                if (input[i] == '<')
                {
                    if (input[i + 1] == '<')
                        i += 2; // <<
                    else
                        i++; // <
                }
                else if (input[i] == '>')
                {
                    if (input[i + 1] == '>')
                        i += 2; // >>
                    else
                        i++; // >
                }
                
                // Ignorer les espaces après la redirection
                while (input[i] && (input[i] == ' ' || input[i] == '\t'))
                    i++;
                
                // Vérifier qu'il y a un fichier après la redirection
                if (!input[i] || input[i] == '|' || input[i] == '<' || input[i] == '>')
                {
                    printf(YELLOW"DEBUG: Syntax error - redirection without file\n"RESET);
                    return (-1);
                }
                
                // Continuer pour trouver la fin du nom de fichier
                while (input[i] && input[i] != ' ' && input[i] != '\t' 
                       && input[i] != '|' && input[i] != '<' && input[i] != '>')
                {
                    if (input[i] == '\'' || input[i] == '\"')
                    {
                        char file_quote = input[i];
                        i++;
                        while (input[i] && input[i] != file_quote)
                            i++;
                        if (input[i] == file_quote)
                            i++;
                    }
                    else
                        i++;
                }
                continue;
            }
        }
        i++;
    }
    return (0);
}

int validate_pipe_syntax(const char *input)
{
    int i = 0;
    char quote = 0;
    int last_was_pipe = 0;
    int found_command = 0;
    
    // Ignorer les espaces au début
    while (input[i] && (input[i] == ' ' || input[i] == '\t'))
        i++;
    
    // Vérifier si la ligne commence par un pipe
    if (input[i] == '|')
    {
        printf(YELLOW"DEBUG: Syntax error - line starts with pipe\n"RESET);
        return (-1);
    }
	if (validate_redirection_syntax(input) != 0)
		return (-1);
    
    while (input[i])
    {
        if (input[i] == '\'' || input[i] == '\"')
        {
            if (!quote)
                quote = input[i];
            else if (quote == input[i])
                quote = 0;
        }
        else if (input[i] == '|' && !quote)
        {
            if (last_was_pipe)
            {
                printf(YELLOW"DEBUG: Syntax error - consecutive pipes\n"RESET);
                return (-1);
            }
            last_was_pipe = 1;
            found_command = 0;
            
            // Vérifier s'il y a quelque chose après le pipe
            int j = i + 1;
            while (input[j] && (input[j] == ' ' || input[j] == '\t'))
                j++;
            if (!input[j] || input[j] == '|')
            {
                printf(YELLOW"DEBUG: Syntax error - pipe at end or followed by pipe\n"RESET);
                return (-1);
            }
        }
        else if (input[i] != ' ' && input[i] != '\t')
        {
            last_was_pipe = 0;
            found_command = 1;
        }
        i++;
    }
    
    // Vérifier si la ligne se termine par un pipe
    if (last_was_pipe)
    {
        printf(YELLOW"DEBUG: Syntax error - line ends with pipe\n"RESET);
        return (-1);
    }
    
    return (0);
}

int count_cmd(t_token_list *token_list)
{
	if (!token_list)
		return 0;
	int count = 1;
	t_token_list *current = token_list;
	while (current)
	{
		if (current->type == PIPE)
			count++;
		current = current->next;
	}
	printf(YELLOW"DEBUG: Nombre de commandes : %d\n"RESET, count);
	return count;
}

t_pipex parse_line(char *line, t_token_list *token_list)
{
	t_pipex pipex;

	t_pipex_init(&pipex, line, token_list);
	if (!pipex.commands)
	{
		ft_putstr_fd(RED"Error: Memory allocation failed\n"RESET, STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	return (pipex);
}

int	parse_input(t_data *data, char *input, t_token_list *token_list)
{
	int		count;
	int		i;
	t_token_list *temp;
	int 	index;

	index = 0;
	if (init_first_value_token_list(input, token_list, &index) == -1)
		return (-1);
	data->input = input;
	count = count_tokens(input);
	if (count > 1)
	{
		i = 1;
		temp = token_list;
		printf(YELLOW"DEBUG COUNT = %d ////// i = %d\n"RESET, count, i);
		while (i < count)
		{
			temp->next = malloc(sizeof(t_token_list));
			if (!temp->next)
			{
				ft_putstr_fd(RED"Error: Memory allocation failed\n"RESET, STDERR_FILENO);
				return (-1);
			}
			temp = temp->next;
			init_token_list(temp);
			temp->token = extract_tokens(input, temp->token, &index);
			if (!temp->token)
				return (-1);
			temp->token = parsed_token(temp->token);
			if (!temp->token)
				return (-1);
			temp->type = get_token_type(temp->token);
			i++;
		}
	}
	printf(YELLOW"DEBUG: FIN de boucle \n"RESET);
	
	return (0);
}
