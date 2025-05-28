/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 14:45:54 by mstasiak          #+#    #+#             */
/*   Updated: 2025/05/28 20:09:25 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*--------------------macro--------------------*/

# define RESET  "\e[0m"
# define RED	"\e[31m"
# define GREEN	"\e[32m"
# define YELLOW	"\e[93m"
# define PINK	"\e[95m"
# define CYAN	"\e[96m"

/*--------------------bibliotheques--------------------*/

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

# include "Libft/libft.h"
# include "get_next_line/get_next_line.h"

/*--------------------structures--------------------*/

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

typedef struct	s_data
{
	char **envp;		// Environment variables
	int exit_status;	// Exit status of the last command
	char *pwd;			// Current working directory
	char *oldpwd;		// Previous working directory
	char *input;		// User input
}				t_data;

typedef struct s_token_list
{
	char	*token;		// Le token lui-même
	int		type;		// Type du token (commande, argument, redirection, etc.)
	struct s_token_list *next; // Pointeur vers le prochain token
} t_token_list;

/*--------------------enumeration--------------------*/

typedef enum e_token_type
{
	TXT,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC,
	PIPE
} t_token_type;

/*--------------------fonctions--------------------*/

// Builtins
void			builtin_cd(char **cmd, t_data *data);
void			echo_builtin(t_token_list *token_list, t_data *data);
int				pwd(t_data *data);
int				env(t_data *data, char *cmd);
int				ft_export(t_data *data, t_token_list *token_list);
int				ft_unset(t_data *data, t_token_list *token_list);
void			exit_builtin(t_data *data, t_cmd *cmd);

// Utils
void			handle_signals(int sig);
void			init_signals(void);
void			free_pipex(t_pipex *pipex);
char			**copy_envp(char **envp);
void			free_data(t_data *data);
void			init_data(t_data *data, char **envp);
char			*new_envp(const char *name, const char *value);
char			**add_envp(char **news, char **envp, const char *name, const char *val);
void			update_env_var(char ***envp, const char *name, const char *value);
char			*get_env_var(char **envp, const char *name);
char			*get_start_cmd(char *cmd);
char			*expand_variables(char *input, t_data *data);
void			free_token_list(t_token_list *token);
void			init_token_list(t_token_list *token_list);
int				init_first_value_token_list(char *input, t_token_list *token_list);

// Pipex
t_cmd			*ft_split_advanced(const char *s, int cmd_count);
char			*find_path(t_data *data, char *cmd_name);
void			execute_pipeline(t_data *data, t_pipex *pipex);
void			execute(t_data *data, t_cmd *cmd);
void			child_process(t_data *data, t_pipex *pipex, int cmd_index);
void			handle_here_doc(t_data *data, t_redirect *redirect);
void			free_tab(char **tab);
void			free_cmd(t_cmd *cmd);
void			error_127(t_data *data, t_cmd *cmd, char *path);
void			error(t_data *data);
void			t_pipex_init(t_pipex *pipex, char *input, t_token_list *current);

// Parsing
t_pipex 		parse_line(char *line, t_token_list *token_list);
int				parse_input(t_data *data, char *input, t_token_list *token_list);
int				count_tokens(char *str);
t_token_type	get_token_type(char *token);
char			*extract_tokens(char *str, char *token);
char			*parsed_token(char *token);
int				single_quoted(char *token, int i);
int				double_quoted(char *token, int i);
int 			count_cmd(t_token_list *token_list);

#endif
