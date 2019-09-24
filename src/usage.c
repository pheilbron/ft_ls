/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usage.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 18:26:52 by pheilbro          #+#    #+#             */
/*   Updated: 2019/09/23 20:57:19 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "ft_ls_options.h"

static char	*get_options(void)
{
	t_dstring	*s;
	int			i;

	s = ft_dstr_init();
	i = 0;
	while (g_options_tab[i].type)
		ft_dstr_add(s, &g_options_tab[i++].type, 1);
	return (ft_dstr_release(s));
}

void		print_usage(void)
{
	char	*options;
	ft_printf("usage: ls [-%s] [file ...]", options = get_options());
	free(options);
}

static void	print_help_aux(void)
{
	ft_printf("FORMAT\t"
			"(-short-option, --format=LONG-OPTION, or --LONG-OPTION)\n"
			" -C vertical		-- list entries in columns sorted vertically\n"
			" -G grid		-- gird format\n"
			" -l verbose		-- long listing\n"
			" -m commas		-- separate by commas\n"
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
	print_usage();
	print_help_aux();
	ft_printf("FILTER\t"
			"(-short-option, --filter=LONG-OPTION, or --LONG-OPTION)\n"
			" -A 			-- list all except . and ..\n"
			" -a all			-- don't ignore entries starting with .\n"
			" -d list-dir		-- list directory entries instead of contents\n"
			" -F 			-- append file type indicators\n"
			" -g no-owner		-- long listing w/out owner information\n"
			" -h 			-- print sizes in human readable form, "
			"ie 1K 234M 2G etc.\n"
			" -i inode		-- print file inode numbers\n"
			" -n numeric-id		-- print numberic uid, gid\n"
			" -o no-group		-- long listing w/out group information\n"
			" -s block-size		-- display size of each file in blocks\n"
			" -T long-time		-- show complete time information\n"
			" -@ extended		-- display extended attributes\n\n");
	ft_printf("OTHER\t(-short-option, --LONG-OPTION)\n"
			" -R recurse		-- list subdirectories recursively\n"
			" -Y tree		-- list subdirectories recursively in tree format\n"
			" -H help		-- print help\n");
}
