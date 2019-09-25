/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 09:35:19 by pheilbro          #+#    #+#             */
/*   Updated: 2019/09/25 14:30:47 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include "ft_ls.h"
#include "ft_ls_options.h"
#include "ft_rbtree.h"
#include "ft_string.h"
#include "ft_error.h"

#define SET(a,b,c) ((a & b) == b ? c : '-')

static char	*set_permissions(struct stat file)
{
	char	*ret;
	char	file_type;

	if (S_ISDIR(file.st_mode))
		file_type = 'd';
	else if (S_ISCHR(file.st_mode))
		file_type = 'c';
	else if (S_ISBLK(file.st_mode))
		file_type = 'b';
	else if (S_ISFIFO(file.st_mode))
		file_type = 'p';
	else if (S_ISLNK(file.st_mode))
		file_type = 'l';
	else if (S_ISSOCK(file.st_mode))
		file_type = 's';
	else
		file_type = '-';
	ft_nsprintf(ret, "%c%c%c%c%c%c%c%c%c%c", file_type,
			SET(file.st_mode, S_IRUSER, 'r'), SET(file.st_mode, S_IWUSER, 'w'),
			SET(file.st_mode, S_IXUSER, 'x'), SET(file.st_mode, S_IRUGRP, 'r'),
			SET(file.st_mode, S_IWUGRP, 'w'), SET(file.st_mode, S_IXUGRP, 'x'),
			SET(file.st_mode, S_IRUOTH, 'r'), SET(file.st_mode, S_IWUOTH, 'w'),
			SET(file.st_mode, S_IXUOTH, 'x'));
	return (ret);
}

static char	*set_date(struct stat file, uint16_t flag)
{
	char	*ret;
	int		i;

	i = 0;
	if (IS_SET(flag, _C, SORT))
		ret = ctime(file.st_ctime);
	else if (IS_SET(flag, _T, SORT))
		ret = ctime(file.st_mtime);
	else
		ret = ctime(file.st_atime);
	while (*ret != ' ')
		ret++;
	ret++;
	if (!IS_SET(flag, _CAP_T, FILTER))
	{
		while (ret[i] != ':')
			i++;
		i++;
		while (ret[i] != ':')
			i++;
		ret[i] = '\0';
	}
	return (ret);
}

int			set_ls_file_data(uint16_t flag,
		t_ls_file **f, char *name, char *dir_prefix)
{
	struct stat	file;
	char		*path;

	if ((path = ft_strjoin(dir_prefix, name)) && stat(path, &file) == 0)
	{
		(*f)->inode = file.st_ino;
		(*f)->block_size = file.st_blocks;
		(*f)->permissions = set_permissions(file);
		(*f)->links = file.st_nlink;
		(*f)->user_id = IS_SET(flag, _N, FILTER) ?
			ft_itoa(file.st_uid) : getpwuid(file.uid)->pw_name;
		(*f)->group_id = IS_SET(flag, _N, FILTER) ?
			ft_itoa(file.st_gid) : getgrgid(file.gid)->gr_name;
		(*f)->size = file.st_size;
		(*f)->date = set_date(file, flag);
		(*f)->name = name;
		(*f)->e.no = 1;
	}
	else
		ft_error_new(&((*d)->e), SYS_ERROR, data[i]);
	return ((*d)->e.no);
}

int			set_ls_dir_data(t_ls_dir **d, char *name, char *dir_prefix)
{
	struct stat	dir;
	char		*path;

	if ((path = ft_strjoin(dir_prefix, name)) && stat(path, &dir) == 0)
	{
		(*d)->name = dir_path;
		(*d)->block_size = dir.st_blocks;
		(*d)->e.no = 1;
	}
	else
		ft_error_new(&((*d)->e), SYS_ERROR, data[i]);
	return ((*d)->e.no);
}

int			parse_ls_file(char *name, char *dir_prefix, uint16_t flag)
{
	t_ls_file	*file;
	char		*path;
	int			fd;

	if (!(path = ft_strjoin(dir_prefix, name)))
		return (SYS_ERROR);
	if (!(file = malloc(sizeof(*file))))
		return (SYS_ERROR);
	if ((fd = open(path, O_RDONLY)) > 0)
	{
		set_ls_file_data(flag, &file, name, dir_prefix);
		file->e.no = 1;
	}
	else
		ft_error_new(&(file->e), INV_FILE, path);
	ft_rbtree_insert(c->files, ft_rbtree_new_node(file));
	return (((t_ls_file *)file)->e.no < 0 ? 0 : 1);
}
