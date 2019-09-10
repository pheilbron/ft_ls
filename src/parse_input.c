/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 15:51:11 by pheilbro          #+#    #+#             */
/*   Updated: 2019/09/09 19:39:58 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include "ft_ls.h"
#include "ft_ls_options.h"

t_ls_option	g_options_tab[] =
{
	{'1', _1, DISPLAY_MASK, "oneline"},
	{'C', _CAP_C, DISPLAY_MASK, "column"},
	{'x', _X, DISPLAY_MASK, "across"},
	{'l', _L, DISPLAY_MASK, "long"},
	{'c', _C, TIME_MASK, ""},
	{'u', _U, TIME_MASK, "accessed"},
	{'r', _R, 0, "reverse"},
	{'t', _T, 0, "created"},
	{'@', _@, 0, "extended"},
	{'d', _D, 0, "list-dirs"},
	{'e', _E, 0, ""},
	{'a', _A, 0, "all"},
	{'R', _CAP_R, 0, "recurse"},
	{0, 0, 0}
};

static int	set_ls_option(t_ls_context *c, char option)
{
	int	i;

	i = 0;
	while (g_options_tab[i].type)
	{
		if (g_options_tab[i].type == option)
		{
			c->flag &= (~g_options_tab[i].mask & g_options_tab[i].flag);
			return (c->e.no = 1);
		}
		i++;
	}
	c->e.data = &option;
	return (c->e.no = INV_OPTION);
}

static int	set_ls_long_option(t_ls_context *c, char *option)
{
	int	i;

	i = 0;
	while (g_options_tab[i].type)
	{
		if (ft_strcmp(g_options_tab[i].long_version, option) == 0)
		{
			c->flag &=
				(~g_options_tab[i].mask & g_options_tab[i].flag);
			return (c->e.no = 1);
		}
		i++;
	}
	c->e.data = option;
	return (c->e.no = INV_OPTION);
}

static int	parse_ls_options(t_ls_context *c, char **data, int len, int *i)
{
	int	data_i;

	while (*i < len && data[*i][0] == '-')
	{
		data_i = 1;
		if (data[*i][data_i] && data[*i][data_i] == '-')
			if (set_ls_long_option(c, data[*i] + ++data_i) < 0)
				return (c->e.no);
		while (data[*i][data_i])
			if (set_ls_option(c, data[*i][data_i++] < 0))
				return (c->e.no);
		(*i)++;
	}
	return (c->e.no = 1);
}

static int	parse_ls_file(t_ls_context *c, char **data, int i)
{
	void	*file;
	DIR		*dir_stream;
	int		fd;

	if ((dir_stream = opendir(data[i])))
	{
		if (!(file = malloc(sizeof(t_ls_dir *))))
			return (c->e.no = SYS_ERROR);
		((t_ls_dir *)file)->entry = readdir(dir_stream);
		closedir(dir_stream);
		((t_ls_dir *)file)->e.no = 1;
		ft_rbtree_add(c->dirs, file, get_sorter(c->flags));
		return ((t_ls_dir *)file->e.no < 0 ? 0 : 1);
	}
	if (!(file = malloc(sizeof(t_ls_file *))))
		return (c->e.no = SYS_ERROR);
	if ((*get_file_stat(c->flags))(data[i], ((t_ls_file *)file)->entry) == -1)
		ft_error_new(&(((t_ls_file *)file).e), INV_FILE, data[i]);
	else
		((t_ls_file *)file)->e.no = 1;
	ft_rbtree_add(c->files, file, get_sorter(c->flags));
	return (((t_ls_file *)file)->e.no < 0 ? 0 : 1);
}

int			parse_input(t_ls_context *c, char **data, int len)
{
	int	i;

	i = 0;
	ft_ls_error_init(&(c->e));
	if (len == 0 && parse_ls_file(c, ".") < 0)
	else if (parse_ls_options(c, data, len, &i) < 0)
		return (print_fatal_error(*c));
	else
		while (i < len && parse_ls_file(c, data, i) != SYS_ERROR)
			i++;
	return (c->e.no < 0 ? 0 : 1);
}
