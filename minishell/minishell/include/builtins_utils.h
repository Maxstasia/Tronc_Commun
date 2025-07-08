/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 16:32:16 by mstasiak          #+#    #+#             */
/*   Updated: 2025/06/18 13:43:52 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_UTILS_H
# define BUILTINS_UTILS_H

/*--------------------macro--------------------*/

/*--------------------bibliotheques--------------------*/

# include "minishell.h"

/*--------------------structures--------------------*/

typedef struct s_export
{
	char	*arg_with_equal;
	char	*equal_sign;
}				t_export;

/*--------------------fonctions--------------------*/

void	builtin_cd(char **cmd, t_data *data);
void	echo_builtin(t_cmd *cmd, t_data *data);
int		pwd(t_data *data);
int		env(t_cmd *cmd, t_data *data);
void	print_export(t_data *data);
int		ft_export(t_cmd *cmd, t_data *data);
int		ft_unset(t_cmd *cmd, t_data *data);
void	exit_builtin(t_data *data, t_cmd *cmd);

int		is_valid_identifier(char *str);
char	*remove_quotes(char *value);
int		update_existing_var(t_data *data, char *arg);
int		add_new_var(t_data *data, char *arg);

#endif
