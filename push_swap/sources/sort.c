/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:13:39 by mstasiak          #+#    #+#             */
/*   Updated: 2025/01/30 14:27:36 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

/* void	push_swap(t_stack *a, t_stack *b)
{
	ft_printf("Début du tri...\n");

	if (a->size <= 3)
	{
		ft_printf("Tri d'une petite pile...\n");
		sort_small_stack(a);
	}
	else
	{
		ft_printf("Tri d'une grande pile...\n");
		sort_large_stack(a, b);
	}

	print_stack(a, "A après push_swap");
	print_stack(b, "B après push_swap");
}

void	sort_small_stack(t_stack *a)
{
	int	first;
	int	second;
	int	third;
	int	temp;

	if (a->size == 2 && a->top->value > a->top->next->value)
	{
		temp = pop(a);
		push(a, pop(a));
		push(a, temp);
	}
	else if (a->size == 3)
	{
		first = a->top->value;
		second = a->top->next->value;
		third = a->top->next->next->value;
		if (first > second && second > third)
		{
			push(a, pop(a));
			push(a, pop(a));
			push(a, pop(a));
		}
		else if (second > first && first > third)
		{
			temp = pop(a);
			push(a, pop(a));
			push(a, temp);
		}
	}
}

void	sort_large_stack(t_stack *a, t_stack *b)
{
	int	pivot;
	int	size;
	int	i;

	if (a->size <= 3)
		return (sort_small_stack(a));

	// ⚡️ On choisit un pivot fixe : ici, le milieu de la pile
	pivot = find_median(a);

	size = a->size;
	i = 0;
	while (i < size)
	{
		if (a->top->value < pivot)
			push(b, pop(a)); // On met les petits dans B
		else
			rotate(a); // On garde les grands dans A
		i++;
	}

	sort_small_stack(a); // On trie les grands dans A
	sort_small_stack(b); // On trie les petits dans B

	while (!is_empty(b))
		push(a, pop(b)); // On remet B dans A
}

int	find_median(t_stack *stack)
{
	t_node	*current;
	int		*values;
	int		i;

	values = malloc(sizeof(int) * stack->size);
	if (!values)
		return (0);
	current = stack->top;
	i = 0;
	while (current)
	{
		values[i++] = current->value;
		current = current->next;
	}
	sort_array(values, stack->size); // Trie un tableau normal
	i = values[stack->size / 2]; // Prend la médiane
	free(values);
	return (i);
}

void sort_array(int *arr, int size)
{
    int i;
    int j;
    int tmp;

    i = 1;
    while (i < size)
    {
        j = i;
        while (j > 0 && arr[j - 1] > arr[j])
        {
            // Affichage avant l'échange
            ft_printf("Echange: %d et %d\n", arr[j - 1], arr[j]);

            // Échange arr[j] et arr[j-1]
            tmp = arr[j];
            arr[j] = arr[j - 1];
            arr[j - 1] = tmp;

            // Afficher l'état de la pile après l'échange
            ft_printf("État de la pile après échange : ");
            for (int k = 0; k < size; k++)
                ft_printf("%d ", arr[k]);
            ft_printf("\n");

            j--;
        }
        i++;
    }
}
 */

/**
 * get_index - Trouve l'index d'un élément dans la pile b.
 * @b: La pile b.
 * @value: La valeur à rechercher.
 * 
 * Retourne l'index de l'élément dans la pile.
 */
int	get_index(t_stack *b, int value)
{
	t_node *current;
	int index;

	if (!b || !b->top)
		return (-1); // Erreur si la pile est vide

	current = b->top;
	index = 0;
	while (current)
	{
		if (current->value == value)
			return (index);
		current = current->next;
		index++;
	}
	return (-1); // Si la valeur n'est pas trouvée
}

/**
 * find_max - Trouve la valeur maximale dans la pile b.
 * @b: La pile b.
 * 
 * Retourne la valeur maximale dans la pile b.
 */
int	find_max(t_stack *b)
{
	t_node *current;
	int max;

	if (!b || !b->top)
		return (-1); // Erreur si la pile est vide

	current = b->top;
	max = current->value;
	while (current)
	{
		if (current->value > max)
			max = current->value;
		current = current->next;
	}
	return (max);
}

/**
 * swap_nodes - Échange deux nœuds adjacents dans la pile.
 * @first: Le premier nœud.
 * @second: Le deuxième nœud.
 */
void	swap_nodes(t_node *first, t_node *second)
{
	int temp;

	// On échange les valeurs
	temp = first->value;
	first->value = second->value;
	second->value = temp;
}

void	push_to_b(t_stack *a, t_stack *b)
{
	int median = find_median(a);
	int size = stack_size(a);
	int pushed = 0;
	int rotated = 0;

	while (pushed < size / 2)
	{
		if (a->top->value < median)
		{
			pb(a, b);
			pushed++;
		}
		else
		{
			ra(a);
			rotated++;
		}
	}
	while (rotated--) // Remet les éléments dans l'ordre initial
		rra(a);
}

void	sort_b(t_stack *b)
{
	t_node *curr;
	int swapped;

	if (!b || !b->top)
		return ;
	do
	{
		swapped = 0;
		curr = b->top;
		while (curr->next)
		{
			if (curr->value < curr->next->value)
			{
				swap_nodes(curr, curr->next);
				swapped = 1;
			}
			curr = curr->next;
		}
	} while (swapped);
}

void	push_to_a(t_stack *a, t_stack *b)
{
	while (b->size > 0)
	{
		int max = find_max(b); // Trouver le plus grand élément de b
		while (b->top->value != max)
		{
			if (get_index(b, max) < b->size / 2)
				rb(b);
			else
				rrb(b);
		}
		pa(a, b);
	}
}

/**
 * stack_size - Calcule la taille d'une pile.
 * @stack: Pile à mesurer.
 * 
 * Retourne le nombre d'éléments dans la pile.
 */
int	stack_size(t_stack *stack)
{
	t_node	*current;
	int		count;

	if (!stack || !stack->top)
		return (0);
	count = 0;
	current = stack->top;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

void	push_swap(t_stack *a, t_stack *b)
{
	if (stack_size(a) <= 1)
		return ;
	push_to_b(a, b);
	sort_b(b);
	push_to_a(a, b);
}
