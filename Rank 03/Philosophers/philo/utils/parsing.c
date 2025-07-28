/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 11:06:03 by mstasiak          #+#    #+#             */
/*   Updated: 2025/04/15 16:11:35 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/**
 * Vérifie si une chaîne contient uniquement des chiffres.
 * 
 * @param str La chaîne à vérifier.
 * @return True si la chaîne contient uniquement des chiffres,
 * False si un caractère n'est pas un chiffre.
 */
static BOOL	contains_only_digits(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	ft_atoi(char *str)
{
	unsigned long long int	nb;
	int						i;

	i = 0;
	nb = 0;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	if (nb > INT_MAX)
		return (-1);
	return ((int)nb);
}

BOOL	is_valid_input(int argc, char **argv)
{
	int	i;
	int	nb;

	i = 1;
	while (i < argc)
	{
		if (!contains_only_digits(argv[i]))
			return (msg(STR_ERR_INPUT_DIGIT, argv[i], FALSE));
		nb = ft_atoi(argv[i]);
		if (i == 1 && (nb <= 0 || nb > MAX_PHILOS))
			return (msg(STR_ERR_INPUT_POFLOW, STR_MAX_PHILOS, FALSE));
		if (i != 1 && nb == -1)
			return (msg(STR_ERR_INPUT_DIGIT, argv[i], FALSE));
		i++;
	}
	return (TRUE);
}
