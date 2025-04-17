#include "minishell.h"


void	ft_cleanup(t_data *data)
{
	if (data->cmd)
	{
		free_tab(data->cmd);
		data->cmd = NULL;
	}
	if (data->envp)
	{
		free_tab(data->envp);
		data->envp = NULL;
	}
	if (data->pwd)
	{
		free(data->pwd);
		data->pwd = NULL;
	}
	if (data->oldpwd)
	{
		free(data->oldpwd);
		data->oldpwd = NULL;
	}
}

static int 	count_tokens(char *input)
{
	int		i;
	int		count;
	char	quote;

	count = 0;
	i = 0;
	if (!input || !*input)
		return (0);
	while (input[i])
	{
		while (input[i] && ft_isspace(input[i]))
			i++;
		if (!input[i])
			break ;
		if (input[i] == '\'' || input[i] == '\"')
		{
			quote = input[i++];
			while (input[i] && input[i] != quote)
				i++;
			if (input[i] == quote)
				i++;
			else
				return (count);
		}
		else
			while (input[i] && !ft_isspace(input[i]))
				i++;
		count++;
	}
	return (count);
}

static int	extract_token(char *input, char **token)
{
	int		i;
	char	quote;
	char	*start;

	i = 0;
	if (!input || !*input)
		return (-1);
	while (input[i] && ft_isspace(input[i]))
		i++;
	start = input + i;
	if (input[i] == '\'' || input[i] == '\"')
	{
		quote = input[i++];
		start = input + i;
		while (input[i] && input[i] != quote)
			i++;
		if (!input[i])
			return (-1);
		*token = ft_substr(start, 0, i - (start - input));
		if (!*token)
			return (-1);
		return (i + 1);
	}
	while (input[i] && !ft_isspace(input[i]))
		i++;
	*token = ft_substr(start, 0, i);
	if (!*token)
		return (-1);

	return (i); 
}

static int	parse_input(t_data *data, char *input)
{
	int	i;
	int	live_index;
	int	count;

	if (!input || !*input)
		return (free_tab(data->cmd), data->cmd = NULL, 0);
	free_tab(data->cmd);
	data->cmd = NULL;
	count = count_tokens(input);
	data->cmd = malloc(sizeof(char *) * (count + 1));
	if (!data->cmd)
		return (ft_putstr_fd("minishell: malloc failed\n", 2), data->exit_status = 1, 1);
	i = 0;
	live_index = 0;
	while (i < count)
	{
		live_index += extract_token(input + live_index, &data->cmd[i]);
		if (live_index < 0 || !data->cmd[i])
		{
			free_tab(data->cmd);
			data->cmd = NULL;
			return (ft_putstr_fd("minishell: Parsing error\n", 2), data->exit_status = 1, 1);
		}
		i++;
	}
	data->cmd[i] = NULL;
	return (0);
}

void	minishell_loop(t_data *data)
{
	char	*input;

	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
		{
			ft_cleanup(data);
			break;
		}
		if (*input)
			add_history(input);
		if (parse_input(data, input) == 0 && data->cmd)
		{
			if (ft_strcmp(data->cmd[0], "unset") == 0)
				unset_builtin(data);
			else if (ft_strcmp(data->cmd[0], "cd") == 0)
				cd_builtin(data);
			else if (ft_strcmp(data->cmd[0], "export") == 0)
				export_builtin(data);
			else if (ft_strcmp(data->cmd[0], "echo") == 0)
				echo_builtin(data);
			else if (ft_strcmp(data->cmd[0], "pwd") == 0)
				pwd_builtin(data);
			else if (ft_strcmp(data->cmd[0], "env") == 0)
				env_builtin(data);
			else if (ft_strcmp(data->cmd[0], "exit") == 0)
				exit_builtin(data);
		}
		free_tab(data->cmd);
		data->cmd = NULL;
		free(input);
	}
}