/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 16:28:48 by mstasiak          #+#    #+#             */
/*   Updated: 2025/01/20 18:05:05 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

/*--------------------macro--------------------*/



/*--------------------bibliotheques--------------------*/

# include <unistd.h>   // Pour read, write
# include <stdlib.h>   // Pour malloc, free, exit

# include "ft_printf.h"

/*--------------------structures--------------------*/

/**
 * struct s_node - Structure chaînon de la pile.
 * 
 * Cette structure est utilisée pour manipuler les données liés aux piles.
 * Les champs permettent de représenter :
 * - @next: Pointeur vers le chaînon suivant dans la pile.
 * - @value: La valeur entière stockée dans le chaînon.
 */
typedef struct s_node {
	struct	s_node	*next;
	int				value;
}							t_node;

/**
 * struct s_stack - Structure représentant une pile.
 * 
 * Cette structure est utilisée comme pile.
 * Les champs permettent de représenter :
 * - @top: Tableau d'entiers.
 * - @size: Taille actuelle de la pile (nb d'éléments).
 */
typedef struct	s_stack {
	t_node	*top;
	int		size;
}							t_stack;



/*--------------------fonctions--------------------*/

/*----------sources----------*/
/*-----error.c-----*/


/*-----input.c-----*/



/*-----instructions.c-----*/



/*-----sort.c-----*/



/*-----stack.c-----*/



/*-----utils.c-----*/



#endif
