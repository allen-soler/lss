/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 16:28:10 by jallen            #+#    #+#             */
/*   Updated: 2019/01/21 22:57:10 by jallen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	swap_list(t_lst *p1, t_lst *p2)
{
	char	*tmp;
	int		i;

	i = p1->data;
	p1->data = p2->data;
	p2->data = i;
	tmp = p1->content;
	p1->content = p2->content;
	p2->content = tmp;
}

void	reverse_child(t_lst **head_ref)
{
	t_lst	*current;
	t_lst	*next;
	t_lst	*prev;

	current = *head_ref;
	next = NULL;
	prev = NULL;
	while (current != NULL)
	{
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	*head_ref = prev;
}

void	sorting(t_lst **current, t_lst **d_path)
{
	if (current)
	{
		if ((g_flag & T) == 0)
			merge_sort(current, 1);
		if (g_flag & T)
			merge_sort(current, 0);
		if (g_flag & RR)
			reverse_child(current);
	}
	if (d_path)
	{
		if ((g_flag & T) < 0)
			merge_sort(d_path, 1);
		if (g_flag & T)
			merge_sort(d_path, 0);
		if (g_flag & RR)
			reverse_child(d_path);
	}
}

void	ft_sortav(int ac, char **av, int start)
{
	char	*tmp;
	int		i;

	i = start;
	while (i < ac - 1)
	{
		if (ft_strcmp(av[i], av[i + 1]) > 0)
		{
			tmp = av[i];
			av[i] = av[i + 1];
			av[i + 1] = tmp;
			i = start;
		}
		i++;
	}
}
