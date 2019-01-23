/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 13:07:02 by jallen            #+#    #+#             */
/*   Updated: 2019/01/23 13:50:34 by jallen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"
#include <stdio.h>

static void	get_time(struct stat date)
{
	char		*f_time;
	struct tm	*foo;
	struct tm	*foo1;
	time_t		rawtime;

	f_time = NULL;
	time(&rawtime);
	foo = localtime(&rawtime);
	foo1 = gmtime(&(date.st_mtime));
	if (foo->tm_mon - foo1->tm_mon <= -6 || foo->tm_mon - foo1->tm_mon >= 6 ||
			foo->tm_year - foo->tm_year <= 2)
	{
		f_time = ft_strsub(ctime(&date.st_mtime), 4, 6);
		ft_printf("%s  ", f_time);
		free(f_time);
		f_time = ft_strdup(&ctime(&date.st_mtime)[20]);
		f_time[ft_strlen(f_time) - 1] = '\0';
		ft_printf("%s ", f_time);
	}
	else
	{
		f_time = ft_strsub(ctime(&date.st_mtime), 4, 12);
		ft_printf("%s ", f_time);
	}
	free(f_time);
}

static void	ls_colors(char *name, char *buf, char *rights, int i)
{
	if (ft_chmod(rights) / 100 == 7 && rights[0] == '-' && g_flag & G)
		ft_printf("{r}%s{R}", name);
	else if (rights[0] == 'd' && g_flag & G)
		ft_printf("{c}%s{R}", name);
	else if (rights[0] == 'l' && g_flag & G)
		ft_printf(C_MAGENTA"%s"C_RESET, name);
	else if (rights[0] == 'c' && g_flag & G)
		ft_printf(C_YELLOW"{b}%s{R}"C_RESET, name);
	else
		ft_printf("%s", name);
	if (rights[0] == 'l')
		ft_printf(" -> %s", buf);
	if (i == 1)
		ft_putchar('\n');
}

static int		num_len(int nb)
{
	int i;

	i = 0;
	while (nb != 0)
	{
		nb /= 10;
		i++;
	}
	return (i);
}

void		ft_ls_l(char *name, char *buf, char *path)
{
	char			*rights;
	int				sp[4];

	rights = 0;
	rights = g_rights(f_stat, rights, path);
	grp = getgrgid(f_stat.st_gid);
	sp[0] = n_sp(g_space.two, (int)f_stat.st_nlink, 0) + 1;
	sp[1] = n_sp(g_space.one, (int)f_stat.st_size, 0) + num_len((int)f_stat.st_size) + 2;
	sp[2] = n_sp(g_space.two, ft_strlen(name), 0);
	sp[3] = n_sp(g_space.two, ft_strlen(name), 0);
	ft_printf("%s ", rights);
	ft_printf("%*d ", sp[0], (int)f_stat.st_nlink);
	if ((pwd = getpwuid(f_stat.st_uid)) != NULL)
		ft_printf("%s  %s", pwd->pw_name, grp->gr_name);
	if (S_ISCHR(f_stat.st_mode) || S_ISBLK(f_stat.st_mode))
		ft_printf("  %5d, %d ", (int32_t)(((f_stat.st_rdev) >> 24) & 0xff),
				(int32_t)((f_stat.st_rdev) & 0xffffff));
	else
		ft_printf("%*d ", sp[1], (int)f_stat.st_size);
	get_time(f_stat);
	ls_colors(name, buf, rights, 1);
	free(rights);
}

void		ft_normal_ls(t_lst *current, char *path)
{
	char	*rights;
	char	*tmp;
	char	buf[1000];
	int		i;

	rights = NULL;
	ft_bzero(buf, 1000);
	while (current)
	{
		i = n_sp(g_space.name, ft_strlen(current->content), 1);
		tmp = ft_strjoin(path, current->content);
		lstat(tmp, &f_stat);
		rights = g_rights(f_stat, rights, tmp);
		ls_colors(current->content, buf, rights, 0);
		nchar(i, 32);
		current = current->next;
	}
	ft_putchar('\n');
	free(rights);
}

void		ft_print_ls(t_lst *head, char *path, int i)
{
	char	*tmp;
	char	buf[1000];

	ft_bzero(buf, 1000);
	if (g_flag & L && (ONE & g_flag) == 0)
	{
		ft_printf("total : %i\n", i);
		while (head)
		{
			tmp = ft_strjoin(path, head->content);
			lstat(tmp, &f_stat);
			readlink(tmp, buf, 1000);
			ft_ls_l(head->content, buf, tmp);
			head = head->next;
			free(tmp);
		}
	}
	else
		ft_normal_ls(head, path);
}
