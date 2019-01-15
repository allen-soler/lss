/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getpath.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 22:19:00 by jallen            #+#    #+#             */
/*   Updated: 2019/01/14 21:25:07 by jallen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static void	sorting(t_lst *current, t_lst **d_path, char *flags)
{
	if (current != NULL)
	{
		if (flags[3] == '0')
			sort_ascii(current->child);
		if (flags[3] == '4')
			sort_int(current->child);
		if (flags[4] == '5')
			reverse_child(&current->child);
	}
	if (d_path)
	{
		if (flags[3] == '0')
			sort_ascii(*d_path);
		if (flags[3] == '4')
			sort_int(*d_path);
		if (flags[4] == '5')
			reverse_child(d_path);
	}
}

void	add_path(char *path, t_lst *head, char *flags)
{
	t_lst			*d_path;
	t_lst			*current;
	DIR				*d;
	char			*tmp;
	time_t			time;

	d_path = NULL;
	if (!(d = opendir(path)))
		return;
	current = add_child(head, path, 0);
	while ((sd = readdir(d)) != NULL)
	{
		time = 0;
		tmp = ft_strjoin(path, sd->d_name);
		lstat(tmp, &f_stat);
		if (f_stat.st_mode > time)
			time = f_stat.st_mtime;
		if (sd->d_name[0] != '.')
			current->data = current->data + f_stat.st_blocks;
		if (sd->d_name[0] != '.' && flags[1] == '0')
			lst_add(&current->child, new_node(sd->d_name, (long)time));	
		if (sd->d_type == DT_DIR && sd->d_name[0] != '.' && flags[1] == '0' && flags[2] == '3')
			lst_add(&d_path, new_node(check_p(sd->d_name, path, 0), (long)time));
		if (sd->d_name[0] && flags[2] == '3')
			lst_add(&current->child, new_node(sd->d_name, (long)time));	
		if (sd->d_type == DT_DIR && ft_strcmp(sd->d_name,".")  != 0 && 
				ft_strcmp(sd->d_name, "..") != 0 && flags[1] == '2' &&flags[2] == '3')
			lst_add(&d_path, new_node(check_p(sd->d_name, path, 0), (long)time));
	}
	sorting(current, &d_path, flags);
	while (d_path)
	{
		add_path(d_path->content, head, flags);
		d_path = d_path->next;
	}
	closedir(d);
}
