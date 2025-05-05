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
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../LIBFT/libft.h"
# include "../LIBFT/get_next_line.h"

typedef struct	s_redirect
{
	char	*type;		// "<", ">", "<<", ">>"
	char	*file;		// Nom du fichier ou délimiteur pour "<<"
}				t_redirect;

typedef struct	s_cmd
{
	char		**args;			// Arguments de la commande
	t_redirect	*redirects;		// Tableau des redirections
	int			redirect_count;	// Nombre de redirections
}				t_cmd;

typedef struct	s_pipex
{
	t_cmd	*commands;	// Tableau des commandes
	int		cmd_count;	// Nombre de commandes
	char	**envp;		// Variables d'environnement
	int		fd[2];		// Pipe actuel
	int		prev_fd;	// Descripteur du pipe précédent
	int		is_first;	// Première commande ?
	int		is_last;	// Dernière commande ?
	pid_t	*pids;		// Tableau des PIDs
}				t_pipex;

typedef struct t_data
{
    char    **envp; // Environment variables
    char    **cmd; // Command arguments parsed
    int     exit_status; // Exit status of the last command
    char    *pwd; // Current working directory
    char    *oldpwd; // Previous working directory
	int		*was_quoted; // Flag to check if the command was quoted
} t_data;

long    ft_atol(const char *str);
char    **copy_envp(char **envp);
void init_data(t_data *data, char **envp);
void    free_data(t_data *data);
void	ft_cleanup(t_data *data);
void	minishell_loop(t_data *data);
void builtin_cd(char **cmd, t_data *data);
char	*new_envp(const char *name, const char *value);
char	**add_envp(char **new, char **envp, const char *name, const char *val);
void	update_env_var(char ***envp, const char *name, const char *value);
char	*get_env_var(char **envp, const char *name);
void echo_builtin(t_data *data);
int env(t_data *data);
void    exit_builtin(t_data *data);
int ft_export(t_data *data);
int pwd(t_data *data);
char *get_start_cmd(char *cmd);
int ft_unset(t_data *data);
void usage(void);
void free_cmd(t_cmd *cmd);
void error_127(t_data *data, t_cmd *cmd, char *path);
void error(t_data *data);
void handle_here_doc(t_data *data, t_redirect *redirect);
void child_process(t_data *data, t_pipex *pipex, int cmd_index);
t_cmd *ft_split_advanced(const char *s);
void execute(t_data *data, t_cmd *cmd);
char *find_path(t_data *data, char *cmd_name);
void execute_pipeline(t_data *data, t_pipex *pipex);
char *expand_variables(char *input, t_data *data);

#endif