/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 20:10:08 by pheilbro          #+#    #+#             */
/*   Updated: 2019/09/09 20:26:22 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_ls(t_rbtree *files, t_rbtree *dirs, uint16_t flag)
{
	t_dstring	*s;

	s = ft_dstr_init();
	while (!ft_rbtree_is_empty(files))
		(*set_print(flag))(ft_rbtree_get_least(files));
	free(files);
	ft_printf("%s", s->buf);
	if ((flag & _CAP_R) == _CAP_R && dirs)
	{
		while (!ft_rbtree_is_empty(dirs))
			ft_ls(set_file_tree((t_ls_dir *)ft_rbtree_get_least(dirs), flag),
					NULL, flag);
		free(dirs);
	}
	ft_dstr_free(s);
}
