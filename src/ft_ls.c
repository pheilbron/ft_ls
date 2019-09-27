/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 20:10:08 by pheilbro          #+#    #+#             */
/*   Updated: 2019/09/26 11:05:32 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdint.h>
#include "ft_ls.h"
#include "ft_ls_options.h"
#include "ft_printf.h"
#include "ft_dstring.h"
#include "ft_rbtree.h"
#include "ft_vector.h"
#include "ft_string.h"

static void	dir_tree_map_parse(t_ls_context *c, t_rb_node *dirs)
{
	t_rbtree	*sub_dir;
	t_ls_file	*cur_dir;

	if (dirs)
	{
		if (dirs->left)
			dir_tree_map_parse(c, dirs);
		cur_dir = (t_ls_file *)(dirs->content);
		ft_dstr_addf(c->printer, "%s/%s\n", c->path->path->buf, cur_dir->name);
		if ((sub_dir = get_files(cur_dir)))
		{
			ft_path_add_dir(c->path, cur_dir->name, ft_strlen(cur_dir->name));
			ft_ls(c, sub_dir);
			ft_rbtree_free(sub_dir);
			ft_path_remove_dir(c->path);
		}
		if (dirs->right)
			dir_tree_map_parse(c, dirs);
	}
}

static void	file_tree_map_print(t_ls_context *c, t_rb_node *files,
		t_rbtree *dirs)
{
	t_vector	*to_print;

	if (!(to_print = malloc(sizeof(*to_print))))
		return ;
	if (files->left)
		file_tree_map_print(c, files->left, dirs);
	if (((t_ls_file *)(files->content))->permissions[0] == 'd')
	{
		if (IS_SET(c->flag, _CAP_Y, RECURSE))
		{
			ft_printf("%s", ft_dstr_dump(c->printer));
			dir_tree_map_parse(c, ft_rbtree_new_node(files->content));
		}
		else
			ft_rbtree_insert(dirs, ft_rbtree_new_node(files->content));
	}
	ft_vect_add(to_print,
			get_print_string(c->flag, (t_ls_file *)(files->content)));
	if (files->right)
		file_tree_map_print(c, files->right, dirs);
	if (!files->parent)
		(*process_print_strings(c->flag))(c->printer, to_print);
}

void		ft_ls(t_ls_context *c, t_rbtree *files)
{
	t_rbtree	*dirs;

	if (!(dirs = ft_rbtree_init()))
		return ;
	ft_dstr_addf(c->printer, "total %d\n", );
	file_tree_map_print(c, files->root, dirs);
	ft_rbtree_free(files);
	ft_printf("%s", ft_dstr_dump(c->printer));
	if (IS_SET(c->flag, _CAP_R, RECURSE) && dirs)
		dir_tree_map_parse(c, dirs->root);
	ft_rbtree_free(dirs);
}
