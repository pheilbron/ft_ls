/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 20:10:08 by pheilbro          #+#    #+#             */
/*   Updated: 2019/09/25 15:05:49 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_ls.h"
#include "ft_ls_options.h"
#include "ft_dstring.h"
#include "ft_rbtree.h"

void	file_tree_map_print(t_rb_node *files, t_rbtree *dirs,
		t_dstring *printer, uint16_t flag)
{
	t_vector	*to_print;

	if (files)
	{
		if (!(to_print = malloc(sizeof(*to_print))))
			return ;
		if (files->left)
			file_tree_map_print(files->left, dirs, printer, flag);
		if (((t_ls_file *)(files->content))->permissions[0] == 'd')
		{
			if (IS_SET(flag, _CAP_Y, RECURSE))
			{
				ft_printf("%s", ft_dstr_dump(printer));
				dir_tree_map_parse(ft_rbtree_new_node(files->content),
						path, printer, flag);
			}
			else
				ft_rbtree_insert(dirs, ft_rbtree_new_node(files->content));
		}
		ft_vect_add((*get_print_string(flag))((t_ls_file *)(files->content)));
		if (files->right)
			file_tree_map_print(files->right, dirs, printer, flag);
		if (!files->parent)
			process_print_strings(s, to_print, flag);
	}
}

void	dir_tree_map_parse(t_rb_node *dirs, t_dstring *path,
		t_dstring *printer, uint16_t flag)
{
	t_rbtree	*sub_dir;

	if (dirs)
	{
		if (dirs->left)
			dir_tree_map_parse(dirs, path, printer, flag);
		ft_dstr_addf(printer, "%s/%s\n", path->buf, dirs->name);
		if ((sub_dir = get_files((t_ls_file *)(dir->content))))
		{
			ft_dstr_add_path(path, dirs->name, ft_strlen(dirs->name));
			ft_ls(sub_dir, path, printer, flag);
			ft_rbtree_free(sub_dir);
			ft_dstr_remove_path(path, dirs->name, ft_strlen(dirs->name));
		}
		if (dirs->right)
			dir_tree_map_parse(dirs, path, printer, flag);
	}
}

void	ft_ls(t_rbtree *files, t_dstring *path,
		t_dstring *printer, uint16_t flag)
{
	t_rbtree	*dirs;

	if (!(dirs = ft_rbtree_init()))
		return ;
	ft_dstr_addf(printer, "total %d\n", );
	file_tree_map_print(files->root, dirs, printer, flag);
	ft_rbtree_free(files);
	ft_printf("%s", ft_dstr_dump(printer));
	if (IS_SET(flag, _CAP_R) && dirs)
		dir_tree_map_parse(dirs->root, printer, flag);
	ft_rbtree_free(dirs);
}
