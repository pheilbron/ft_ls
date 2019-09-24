/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 15:51:11 by pheilbro          #+#    #+#             */
/*   Updated: 2019/09/23 20:46:49 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include "ft_ls.h"
#include "ft_ls_options.h"

/* FORMAT:
 * --format=WORD or --WORD
 * -1 single-column	-- single column output
 * -C vertical		-- list entries in columns sorted vertically
 * -G grid			-- gird format
 * -l verbose		-- long listing
 * -m commas		-- separate by commas
 * -x horizontal	-- list entries in columns sorted horizontally
 * -q color			-- print with colors
 * precedence: ((go)/l/1/m C/x) : 3 bits
 * go > l
 * m > C/x
 * otherwise one a pop
 *
 * SORT:
 * --sort=WORD
 * -S size			-- sort by size
 * -c change-time	-- sort by change time
 * -f none			-- output is not sorted
 * -r reverse		-- reverse sort order
 * -t modify-time	-- sort by modification time
 * -u access-time	-- sort by access time
 * -N name			-- sort by name
 * precedence: f S c
 *
 * FILTER:
 * -A 				-- list all except . and ..
 * -F 				-- append file type indicators
 * -T long-time		-- show complete time information
 * -a all			-- don't ignore entries starting with .
 * -d list-dir		-- list directory entries instead of contents
 * -g no-owner		-- long listing w/out owner information
 * -h 				-- print sizes in human readable form, ie 1K 234M 2G etc.
 * -i inode			-- print file inode numbers
 * -n numeric-id	-- print numberic uid, gid
 * -o no-group		-- long listing w/out group information
 * -s block-size	-- display size of each file in blocks
 * -@ extended		-- display extended attributes
 *
 * -R recurse	-- list subdirectories recursively
 * -Y tree		-- list subdirectories recursively in tree format
*/

#define NODE(a,b,c,d,e,l,r) &(t_btree_node){(t_ls_option){a,b,c,d,e}, l, r}
#define END(a,b,c,d,e) &(t_btree_node){(t_ls_option){a,b,c,d,e}, NULL, NULL}

t_btree_node	*g_option_tree = NODE('f', _F, FILTER, "", "",
		NODE('R', _CAP_R, 0, "recurse", "",
			NODE('C', _CAP_C, FORMAT, "vertical", "format=",
				NODE('@', _@, FILTER, "extended", "filter=",
					END('1', _1, FORMAT, "single-column", "format="),
					END('A', _CAP_A, FILTER, "", "")),
				NODE('G', _CAP_G, FORMAT, "grid", "format=",
					END('F', _CAP_F, FILTER, "", ""),
					END('N', _CAP_N, SORT, "name", "sort="))),
			NODE('Y', _CAP_Y, 0, "tree", "",
				NODE('T', _CAP_T, FILTER, "long-time", "filter=",
					END('S', _CAP_S, SORT, "size", "sort="),
					NULL),
				NODE('c', _C, SORT, "change-time", "sort=",
					END('a', _A, FILTER, "all", "filter="),
					END('d', _D, 0, "list-dir", "filter=")))),
		NODE('o', _O, FILTER, "no-group", "filter=",
			NODE('i', _I, FILTER, "inode", "filter=",
				NODE('h', _H, FILTER, "", "",
					END('g', _G, FILTER, "no-owner", "filter="),
					NULL),
				NODE('m', _M, FORMAT, "commas", "format=",
					END('l', _L, FORMAT, "long", "format="),
					END('n', _N, FILTER, "numeric-id", "filter="))),
			NODE('s', _S, FILTER, "block-size", "filter=",
				NODE('r', _R, SORT, "reverse", "sort=",
					END('q', _C, FORMAT, "color", "format="),
					NULL),
				NODE('u', _U, SORT, "access-time", "sort=",
					END('t', _T, SORT, "modify-time", "sort="),
					END('x', _X, FORMAT, "horizontal", "format=")))));

t_ls_option	g_options_tab[] =
{
	{'1', _1, FORMAT, "single-column", "format="},
	{'@', _@, FILTER, "extended", "filter="},
	{'A', _CAP_A, FILTER, "", ""},
	{'G', _CAP_G, FORMAT, "grid", "format="},
	{'C', _CAP_C, FORMAT, "vertical", "format="},
	{'F', _CAP_F, FILTER, "", ""},
	{'N', _CAP_N, SORT, "name", "sort="},
	{'R', _CAP_R, 0, "recurse", ""},
	{'S', _CAP_S, SORT, "size", "sort="},
	{'T', _CAP_T, FILTER, "long-time", "filter="},
	{'Y', _CAP_Y, 0, "tree", ""},
	{'a', _A, FILTER, "all", "filter="},
	{'c', _C, SORT, "change-time", "sort="},
	{'d', _D, 0, "list-dir", "filter="},
	{'f', _F, FILTER, "", ""},
	{'g', _G, FILTER, "no-owner", "filter="},
	{'h', _H, FILTER, "", ""},
	{'i', _I, FILTER, "inode", "filter="},
	{'l', _L, FORMAT, "long", "format="},
	{'m', _M, FORMAT, "commas", "format="},
	{'n', _N, FILTER, "numeric-id", "filter="},
	{'o', _O, FILTER, "no-group", "filter="},
	{'q', _C, FORMAT, "color", "format="},
	{'r', _R, SORT, "reverse", "sort="},
	{'s', _S, FILTER, "block-size", "filter="},
	{'t', _T, SORT, "modify-time", "sort="},
	{'u', _U, SORT, "access-time", "sort="},
	{'x', _X, FORMAT, "horizontal", "format="},
	{0, 0, 0}
};

static int	is_long_option(char *option, t_ls_option *op)
{
	if (!op->long_op)
		return (0);
	else if (ft_strcmp(option, op->long_op) == 0)
		return (1);
	else if (ft_strcatcmp(option, "", op->prefix, op->long_op) == 0)
		return (1);
	else
		return (0);
}

static int	set_ls_option_btree(t_ls_context *c, char *option, uint8_t type)
{
	t_btree_node	*i;
	t_ls_option 	*op;

	i = g_options_tree;
	while (i)
	{
		op = (t_ls_option *)(i->content);
		if ((type == SHORT_OP && *option == op->type) ||
				(type == LONG_OP && is_long_option(option, op)))
		{
			c->flag &= (~op->mask & op->flag);
			return (c->e.no = 1);
		}
		else if (*option < op->type)
			i = i->left;
		else
			i = i->right;
	}
	c->e.data = option;
	return (c->e.no = (type == SHORT_OP ? INV_OPTION : INV_LONG_OPTION));
}

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
			c->flag &= (~g_options_tab[i].mask & g_options_tab[i].flag);
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
