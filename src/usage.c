/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usage.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 18:26:52 by pheilbro          #+#    #+#             */
/*   Updated: 2019/09/26 09:27:27 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_ls.h"
#include "ft_ls_options.h"
#include "ft_printf.h"
#include "ft_btree.h"
#include "ft_dstring.h"

static void	get_options(t_btree_node *options, t_dstring *s)
{
	if (options)
	{
		if (options->left)
			get_options(options->left, s);
		ft_dstr_add(s, &(((t_ls_option)(options->content)).type), 1);
		if (options->right)
			get_options(options->right, s);
	}
}

void		print_usage(void)
{
	t_dstring	*s;

	s = ft_dstr_init();
	get_options(g_options_tree, s);
	ft_printf("usage: ls [-%s] [file ...]", s->buf);
	ft_dstr_free(s);
}

static void	print_help_aux(void)
{
	ft_printf("FORMAT\t"
			"(-short-option, --format=LONG-OPTION, or --LONG-OPTION)\n"
			" -C vertical		-- list entries in columns sorted vertically\n"
			" -G grid		-- gird format\n"
			" -g no-owner		-- long listing w/out owner information\n"
			" -l verbose		-- long listing\n"
			" -m commas		-- separate by commas\n"
			" -o no-group		-- long listing w/out group information\n"
			" -q color		-- print with colors\n"
			" -x horizontal		-- list entries in columns sorted "
			"horizontally\n"
			" -1 single-column	-- single column output\n\n");
	ft_printf("SORT\t(-short-option or --sort=LONG-OPTION)\n"
			" -c change-time		-- sort by change time\n"
			" -f none		-- output is not sorted\n"
			" -N name		-- sort by name\n"
			" -r reverse		-- reverse sort order\n"
			" -S size		-- sort by size\n"
			" -t modify-time		-- sort by modification time\n"
			" -u access-time		-- sort by access time\n\n");

void		print_help(void)
{
	print_help_aux();
	ft_printf("FILTER\t"
			"(-short-option, --filter=LONG-OPTION, or --LONG-OPTION)\n"
			" -A 			-- list all except . and ..\n"
			" -a all			-- don't ignore entries starting with .\n"
			" -d list-dir		-- list directory entries instead of contents\n"
			" -F 			-- append file type indicators\n"
			" -h 			-- print sizes in human readable form, "
			"ie 1K 234M 2G etc.\n"
			" -i inode		-- print file inode numbers\n"
			" -n numeric-id		-- print numberic uid, gid\n"
			" -s block-size		-- display size of each file in blocks\n"
			" -T long-time		-- show complete time information\n"
			" -@ extended		-- display extended attributes\n\n");
	ft_printf("OTHER\t(-short-option, --LONG-OPTION)\n"
			" -R recurse		-- list subdirectories recursively\n"
			" -Y tree		-- list subdirectories recursively in tree format\n"
			" -H help		-- print help\n");
}
