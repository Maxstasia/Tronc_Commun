/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 16:32:16 by mstasiak          #+#    #+#             */
/*   Updated: 2025/05/13 16:05:24 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_UTILS_H
# define BUILTINS_UTILS_H

/*--------------------macro--------------------*/

/*--------------------bibliotheques--------------------*/

# include "minishell.h"

/*--------------------structures--------------------*/

typedef struct	s_export
{
	char	*arg_with_equal;
	char	*equal_sign;
}				t_export;

/*--------------------fonctions--------------------*/

void	print_export(t_data *data);

int		is_valid_identifier(char *str);
char	*remove_quotes(char *value);
int		update_existing_var(t_data *data, char *arg);
int		add_new_var(t_data *data, char *arg);

#endif
