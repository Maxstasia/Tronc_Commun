#include "../minishell.h"

static int check_echo_n(t_data *data, int *i)
{
    int print_newline;

    print_newline = 1;
    *i = 1;
    if (!data->cmd[*i])
        return (print_newline);
    while (data->cmd[*i])
    {
        if ((data->cmd[*i][0] != '-') || (data->cmd[*i][1] != 'n'))
            break;
        if (data->cmd[*i][2] != '\0')
            break;
        print_newline = 0;
        (*i)++;
    }
    return (print_newline);
}

static void print_echo(char **cmd, int i)
{
    while (cmd[i])
    {
        ft_putstr_fd(cmd[i], 1);
        if (cmd[i + 1] != NULL)
            ft_putchar_fd(' ', 1);
        i++;
    }
}

void echo_builtin(t_data *data)
{
    int i;
    int print_newline;

    i = 0;
    print_newline = check_echo_n(data->cmd, &i);
    print_echo(data->cmd, i);
    if (print_newline)
        ft_putchar_fd('\n', 1);
    data->exit_status = 0;
}