/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 15:51:11 by pheilbro          #+#    #+#             */
/*   Updated: 2019/09/26 09:42:09 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include "ft_ls.h"
#include "ft_ls_options.h"
#include "ft_ls_utils.h"
#include "ft_btree.h"
#include "ft_rbtree.h"
#include "ft_string.h"
#include "ft_error.h"

/* FORMAT:
 * --format=WORD or --WORD
 * -1 single-column	-- single column output
 * -C vertical		-- list entries in columns sorted vertically
 * -G grid			-- gird format
 * -g no-owner		-- long listing w/out owner information
 * -o no-group		-- long listing w/out group information
 * -l verbose		-- long listing
 * -m commas		-- separate by commas
 * -x horizontal	-- list entries in columns sorted horizontally
 * -q color			-- print with colors
 * precedence: (l/1/m C/x) : 3 bits
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
 * -h 				-- print sizes in human readable form, ie 1K 234M 2G etc.
 * -i inode			-- print file inode numbers
 * -n numeric-id	-- print numberic uid, gid
 * -s block-size	-- display size of each file in blocks
 * -@ extended		-- display extended attributes
 *
 * -R recurse	-- list subdirectories recursively
 * -Y tree		-- list subdirectories recursively in tree format
*/

#define NODE(a,b,c,d,e,l,r) &(t_btree_node){&(t_ls_option){a,b,c,d,e}, l, r}
#define END(a,b,c,d,e) &(t_btree_node){&(t_ls_option){a,b,c,d,e}, NULL, NULL}

t_btree_node	*g_option_tree = NODE('f', _F, FILTER, "", "",
		NODE('R', _CAP_R, 0, "recurse", "",
			NODE('C', _CAP_C, FORMAT, "vertical", "format=",
				NODE('@', _AT, FILTER, "extended", "filter=",
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
		NODE('o', _O, FORMAT, "no-group", "format=",
			NODE('i', _I, FILTER, "inode", "filter=",
				NODE('h', _H, FILTER, "", "",
					END('g', _G, FORMAT, "no-owner", "format="),
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
	if (*option == 'H' || ft_strcmp(option, "help") == 0)
		return (c->e.no = HELP);
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

static int	parse_ls_input_file(t_ls_context *c, t_rbtree *files, char **data, int i)
{
	t_ls_file	*file;
	int			fd;

//	if ((fd = open(data[i], O_DIRECTORY)) >= 0)
//	{
//		if (!(dir = malloc(sizeof(*dir))))
//			return (c->e.no = SYS_ERROR);
//		set_ls_dir_data(&dir, data[i], "");
//		dir->e.no = 1;
//		ft_rbtree_insert(c->dirs, ft_rbtree_new_node(dir));
//	}
	if (!(file = malloc(sizeof(*file))))
		return (c->e.no = SYS_ERROR);
	if ((fd = open(data[i], O_RDONLY)) > 0)
	{
		set_ls_file_data(c->flag, &file, data[i], "");
		file->e.no = 1;
	}
	else
		ft_error_new(&(file->e), INV_FILE, data[i]);
	ft_rbtree_insert(files, ft_rbtree_new_node(file));
	return (((t_ls_file *)file)->e.no < 0 ? 0 : 1);
}

int			parse_input(t_ls_context *c, t_rbtree *files, char **data, int len)
{
	int	i;

	i = 0;
	ft_ls_error_init(&(c->e));
	if (len == 0 && parse_ls_file(c, ".") < 0)
		return (ft_error_print_std_message("ft_ls", c->e));
	else if (parse_ls_options(c, data, len, &i) < 0)
		return (ft_error_print_std_message("ft_ls", c->e));
	else
	{
		c->compare = (*get_sort(void *, void *))(c->flag);
		while (i < len && parse_ls_input_file(c, files, data, i) != SYS_ERROR)
			i++;
	}
	return (c->e.no < 0 ? 0 : 1);
}
