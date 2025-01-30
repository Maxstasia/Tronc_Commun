/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quick_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 12:58:00 by mstasiak          #+#    #+#             */
/*   Updated: 2025/01/30 13:30:30 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

/**
 * swap - Échange deux entiers dans un tableau.
 * @a: Premier entier.
 * @b: Deuxième entier.
 */
static void	swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

/**
 * ft_quick_sort - Implémente le tri rapide (QuickSort).
 * @arr: Tableau à trier.
 * @low: Indice de début.
 * @high: Indice de fin.
 */
static void	quick_sort(int *arr, int low, int high)
{
	int i = low, j = high, pivot = arr[(low + high) / 2];

	while (i <= j)
	{
		while (arr[i] < pivot)
			i++;
		while (arr[j] > pivot)
			j--;
		if (i <= j)
		{
			swap(&arr[i], &arr[j]);
			i++;
			j--;
		}
	}
	if (low < j)
		quick_sort(arr, low, j);
	if (i < high)
		quick_sort(arr, i, high);
}

int	find_median(t_stack *stack)
{
	int		*arr;
	int		i = 0, median;
	t_node	*current = stack->top;
	int		size = stack_size(stack);

	if (size == 0)
		return (0);
	arr = malloc(sizeof(int) * size);
	if (!arr)
		return (0);
	while (current)
	{
		arr[i++] = current->value;
		current = current->next;
	}
	quick_sort(arr, 0, size - 1);
	median = arr[size / 2];
	free(arr);
	return (median);
}