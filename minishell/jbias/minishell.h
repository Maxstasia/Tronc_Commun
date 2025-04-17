#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

typedef struct t_data
{
    char    **envp; // Environment variables
    char    **cmd; // Command arguments parsed
    int     exit_status; // Exit status of the last command
    char    *pwd; // Current working directory
    char    *oldpwd; // Previous working directory
} t_data;

long    ft_atol(const char *str);

#endif