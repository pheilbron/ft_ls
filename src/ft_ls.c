/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 20:10:08 by pheilbro          #+#    #+#             */
/*   Updated: 2019/09/25 12:14:41 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_ls.h"
#include "ft_ls_options.h"
#include "ft_dstring.h"
#include "ft_rbtree.h"

void	ft_ls(t_rbtree *files, t_rbtree *dirs, t_dstring *s, uint16_t flag)
{
	while (!ft_rbtree_is_empty(files))
		(*set_print(flag))(s, ft_rbtree_get_least(files));
	free(files);
	ft_printf("%s", s->buf);
	if ((flag & _CAP_R) == _CAP_R && dirs)
	{
		while (!ft_rbtree_is_empty(dirs))
			ft_ls(set_file_tree((t_ls_dir *)ft_rbtree_get_least(dirs), flag),
					set_dir_tree((t_ls_dir *)ft_rbtree_get_least(dir), flag),
					s, flag);
		free(dirs);
	}
}
