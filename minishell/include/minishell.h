/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 14:45:54 by mstasiak          #+#    #+#             */
/*   Updated: 2025/06/27 15:31:01 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*--------------------macro--------------------*/

# define RESET  	"\e[0m"
# define RED		"\e[31m"
# define GREEN		"\e[32m"
# define YELLOW		"\e[93m"
# define PINK		"\e[95m"
# define CYAN		"\e[96m"

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

typedef struct s_quote
{
	int		i;
	int		j;
	int		in_quotes;
	char	quote;
}				t_quote;

typedef struct s_tmp
{
	int	x;
	int	y;
}	t_tmp;

typedef struct s_data
{
	char	**envp;
	int		exit_status;
	char	*pwd;
	char	*oldpwd;
	t_tmp	*tmp;
	int		saved_stdin;
	int		saved_stdout;
	int		has_saved_fds;
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
/*----------builtins----------*/
/*-----utils_builtin.c-----*/
int				is_builtin(char *cmd);
void			execute_builtin(t_data *data, t_token_list *token_list,
					t_cmd *cmd);

/*----------parsing----------*/
/*-----lexer_redir.c-----*/
char			*if_pipe(char *input, char *token, int *i, int *index);
char			*if_redir_in(char *input, char *token, int *i, int *index);
char			*if_redir_out(char *input, char *token,	int *i, int *index);

/*-----lexer.c-----*/
int				count_tokens(char *str);
t_token_type	get_token_type(char *token);
char			*extract_tokens(char *str, char *token, int *index);

/*-----parser.c-----*/
int				single_quoted(char *token, int i);
int				double_quoted(char *token, int i);
char			*parsed_token(char *token);

/*-----parsing_pipe.c-----*/
int				validate_pipe_syntax(char *input);

/*-----parsing.c-----*/
int				count_redir(t_cmd *cmd);
int				count_cmd(t_token_list *token_list);
t_pipex			parse_line(char *line, t_token_list *token_list,
					t_pipex *pipex);
int				parse_input(char *input, t_token_list *token_list);

/*-----redir.c-----*/
char			set_quote(char *input, int i, char quote);
int				validate_redirection_syntax(const char *input);
int				has_file_after_redirection(const char *input,
					const char *redir);

/*-----------------pipex-----------------*/
/*----------pipex_sources----------*/
/*-----error.c-----*/
void			malloc_failed(t_data *data);
void			free_tab(char **tab);
void			free_cmd(t_cmd *cmd);
void			error_127(t_data *data, t_cmd *cmd, char *path);
void			error(t_data *data);

/*-----heredoc.c-----*/
void			handle_here_doc(t_data *data, t_redirect *redirect);

/*-----pipex_redir.c-----*/
void			apply_redirects(t_data *data, t_cmd *cmd,
					t_redirect *redirect);

/*-----pipex.c-----*/
void			child_process(t_data *data, t_pipex *pipex, int cmd_index);

/*-----------------pipex-----------------*/
/*----------pipex_utils----------*/
/*-----ft_split_advanced.c-----*/
t_cmd			*ft_split_advanced(char *s, int cmd_count);

/*-----ft_split_advanced2.c-----*/
t_cmd			*init_cmd_array(int cmd_count);
int				is_redirect(char *str);
int				count_token_split(char *input);

/*-----ft_split_advanced3.c-----*/
void			free_cmds(t_cmd *cmd, int j);
int				allocate_cmd_memory(t_cmd *cmd, char *s, int i);
int				extract_token_split(char *input, int *i, char **token);

/*-----quotes.c-----*/
char			*process_quotes(char *str, char *quotes_free);

/*-----quotes2.c-----*/
char			*remove_quotes_split(char *str);
int				handle_escaped_quote(char *str, char *quotes_free,
					t_quote *data);

/*-----utils_pipex.c-----*/
void			update_env_var(char ***envp, const char *name,
					const char *value);
char			*get_env_var(char **envp, const char *name);

/*-----utils2_pipex.c-----*/
void			check_hdoc_fd(int *last_heredoc_fd);
char			*find_path(t_data *data, char *cmd_name);
void			execute(t_data *data, t_cmd *cmd);
void			t_pipex_init(t_pipex *pipex, char *input,
					t_token_list *current);

/*----------pipex----------*/
/*-----pipex_executor.c-----*/
void			execute_pipeline(t_data *data, t_pipex *pipex);

/*----------utils----------*/
/*-----cleanup.c-----*/
void			free_token_list(t_token_list **token_list);
void			free_pipex(t_pipex *pipex, int bool);
void			free_data(t_data *data);
void			free_data_fields(t_data *data);

/*-----cleanup2.c-----*/
void			free_data_envp(t_data *data);

/*-----envp.c-----*/
char			**copy_envp(char **envp);
char			*new_envp(const char *name, const char *value);
char			**add_envp(char **news, char **envp,
					const char *name, const char *val);

/*-----init.c-----*/
void			init_signals(void);
void			init_data(t_data *data, char **envp);
void			init_token_list(t_token_list *token_list);
int				init_first_value_token_list(char *input,
					t_token_list *token_list, int *index);
void			init_pipex(t_pipex *pipex);

/*-----redirection_case_utils.c-----*/
char			*cas_1(char *line, char *trimmed);
char			*cas_2(char *line, char *trimmed);
char			*cas_3(char *line, char *trimmed);
char			*cas_4(char *line, char *trimmed);
char			*cas_5(char *line);

/*-----utils.c-----*/
char			*get_var_name(const char *input, int *i);
int				expand_variable(char *input, char *result, int *i,
					t_data *data);
int				should_expand_variable(char *input, int i, char quote);
int				process_character(char *input, char *result, t_data *data,
					char quote);
char			*expand_variables(char *input, t_data *data);

/*-----utils2.c-----*/
void			handle_signals(int sig);
void			handle_quote(char c, char *quote);
int				handle_escaped_dollar(char *input, char *result,
					int *i, int *j);
char			*get_variable_value(char *var_name, t_data *data);

/*-----utils3.c-----*/
size_t			calculate_buffer_size(char *input, t_data *data);
void			close_saved_fds(t_data *data);

/*----------$PATH----------*/
/*-----minishell.c-----*/
int				validate_syntax(char *expanded_line);
void			handle_command_execution(t_data *data, t_token_list *token_list,
					t_pipex *pipex, char *expanded_line);

/*-----minishell2.c-----*/
int				process_input_line(t_data *data, char *line,
					t_token_list *token_list);

#endif
