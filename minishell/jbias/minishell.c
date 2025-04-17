#include "minishell.h"

void    free_data(t_data *data)
{
    int i;

    if (data->envp)
    {
        while (data->envp[i])
            free(data->envp[i++]);
        free(data->envp);
    }
    if (data->cmd)
        free(data->cmd);
    if (data->pwd)
        free(data->pwd);
    if (data->oldpwd)
        free(data->oldpwd);
}

void init_data(t_data *data, char **envp)
{
    data->envp = copy_envp(envp);
    if (data->envp == NULL)
    {
        ft_putstr_fd("minishell: envp copy failed\n", 2);
        exit(EXIT_FAILURE);
    }
    data->cmd = NULL;
    data->exit_status = 0;
    data->pwd = getcwd(NULL, 0);
    if (data->pwd == NULL)
    {
        ft_putstr_fd("minishell: getcwd", 2);
        exit(EXIT_FAILURE);
    }
    data->oldpwd = NULL;
}

char    **copy_envp(char **envp)
{
    int     i;
    char    **new_envp;

    i = 0;
    while (envp[i])
        i++;
    new_envp = malloc(sizeof(char *) * (i + 1));
    if (!new_envp)
    {
        ft_putstr_fd("minishell: malloc failed\n", 2);
        return (NULL);
    }
    while (envp[i])
    {
        new_envp[i] = ft_strdup(envp[i]);
    }
}

int main(int ac, char **av, char **envp)
{
    char *line;

    (void)av;
    if (ac < 2)
    {
        ft_putstr_fd("Error: ./minishell takes no argument\n", 2);
        return (1);
    }
    while (1)
    {
        line = readline("minishell$ ");
        if (!line)
        {
            printf("exit\n");
            break;
        }
        if (*line)
            add_history(line);
        /* À ajouter plus tard : parsing et exécution */
        printf("Ligne lue : %s\n", line);
        free(line);
    }
    return (0);
}