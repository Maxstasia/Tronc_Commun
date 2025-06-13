/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 14:45:54 by mstasiak          #+#    #+#             */
/*   Updated: 2025/06/13 15:49:59 by mstasiak         ###   ########.fr       */
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

typedef struct s_redirect
{
	char	*type;
	char	*file;
	int		is_heredoc_fd;
}				t_redirect;

typedef struct s_cmd
{
	char		**args;
	t_redirect	*redirects;
	int			redirect_count;
}				t_cmd;

typedef struct s_pipex
{
	t_cmd	*commands;
	int		cmd_count;
	char	**envp;
	int		fd[2];
	int		prev_fd;
	int		is_first;
	int		is_last;
	pid_t	*pids;
}				t_pipex;

typedef struct s_data
{
	char	**envp;
	int		exit_status;
	char	*pwd;
	char	*oldpwd;
	char	*input;
}				t_data;

typedef struct s_token_list
{
	char				*token;
	int					type;		
	struct s_token_list	*next;
}	t_token_list;

/*--------------------enumeration--------------------*/

typedef enum e_token_type
{
	TXT,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC,
	PIPE
}	t_token_type;

/*--------------------fonctions--------------------*/

/* Builtins */
void			builtin_cd(char **cmd, t_data *data);
void			echo_builtin(t_cmd *cmd, t_data *data);
int				pwd(t_data *data);
int				env(t_cmd *cmd, t_data *data);
int				ft_export(t_cmd *cmd, t_data *data);
int				ft_unset(t_cmd *cmd, t_data *data);
void			exit_builtin(t_data *data, t_cmd *cmd);
int				is_builtin(char *cmd);
void			execute_builtin(t_data *data,
					t_token_list *token_list, t_cmd *cmd);

/* Utils */
void			handle_signals(int sig);
void			init_signals(void);
void			free_pipex(t_pipex *pipex);
char			**copy_envp(char **envp);
void			free_data(t_data *data);
void			init_data(t_data *data, char **envp);
char			*new_envp(const char *name, const char *value);
char			**add_envp(char **news, char **envp,
					const char *name, const char *val);
void			update_env_var(char ***envp, const char *name,
					const char *value);
char			*get_env_var(char **envp, const char *name);
char			*expand_variables(char *input, t_data *data);
void			free_token_list(t_token_list *token);
void			init_token_list(t_token_list *token_list);
int				init_first_value_token_list(char *input,
					t_token_list *token_list, int *index);
void			error_malloc(void);

/* Pipex */
t_cmd			*ft_split_advanced(char *s, int cmd_count);
char			*find_path(t_data *data, char *cmd_name);
void			execute_pipeline(t_data *data, t_pipex *pipex);
void			execute(t_data *data, t_cmd *cmd);
void			child_process(t_data *data, t_pipex *pipex, int cmd_index);
void			handle_here_doc(t_data *data, t_redirect *redirect);
void			free_tab(char **tab);
void			free_cmd(t_cmd *cmd);
void			error_127(t_data *data, t_cmd *cmd, char *path);
void			error(t_data *data);
void			t_pipex_init(t_pipex *pipex, char *input,
					t_token_list *current);

/* Parsing */
t_pipex			parse_line(char *line, t_token_list *token_list);
int				parse_input(t_data *data, char *input,
					t_token_list *token_list);
int				count_tokens(char *str);
t_token_type	get_token_type(char *token);
char			*extract_tokens(char *str, char *token, int *index);
char			*parsed_token(char *token);
int				single_quoted(char *token, int i);
int				double_quoted(char *token, int i);
int				count_cmd(t_token_list *token_list);
void			apply_redirects(t_data *data, t_cmd *cmd);
int				validate_pipe_syntax(const char *input);
int				validate_redirection_syntax(const char *input);
int				has_file_after_redirection(const char *input,
					const char *redir);
char			*if_pipe(char *input, char *token, int *i, int *index);
char			*if_redir_in(char *input, char *token, int *i, int *index);
char			*if_redir_out(char *input, char *token,	int *i, int *index);
char			with_quotes(int i, const char *input, char quote);

#endif
