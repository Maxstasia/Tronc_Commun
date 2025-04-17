#include "../minishell.h"

long    ft_atol(const char *str)
{
    long    result;
    int     sign;

    result = 0;
    sign = 1;
    while (*str == ' ' || (*str >= 9 && *str <= 13))
        str++;
    if (*str == '-' || *str == '+')
    {
        if (*str == '-')
            sign = -1;
        str++;
    }
    while (ft_isdigit(*str))
    {
        result = result * 10 + (*str - '0');
        str++;
    }
    return (result * sign);
}

static int  isnum(char *str)
{
    int i;

    i = 0;
    if (str[i] == '-' || str[i] == '+')
        i++;
    while (str[i])
    {
        if (!ft_isdigit(str[i]))
            return (0);
        i++;
    }
    return (1);
}

void    exit_builtin(t_data *data)
{
    long exit_status;

    ft_putstr_fd("exit\n", 2);
    if (!data->cmd[1])
    {
        free_data(data);
        exit(data->exit_status);
    }
    if (!isnum(data->cmd[1]))
    {
        ft_putstr_fd("minishell: exit: ", 2);
        ft_putstr_fd(data->cmd[1], 2);
        ft_putstr_fd(": numeric argument required\n", 2);
        free_data(data);
        exit(255);
    }
    if (data->cmd[2])
    {
        ft_putstr_fd("minishell: exit: too many arguments\n", 2);
        data->exit_status = 1;
        return ;
    }
    data->exit_status = ft_atol(data->cmd[1]);
    data->exit_status = data->exit_status % 256;
    exit(data->exit_status);
}