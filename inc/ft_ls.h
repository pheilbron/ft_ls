/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 15:51:40 by pheilbro          #+#    #+#             */
/*   Updated: 2019/09/25 15:08:00 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS
# define FT_LS

# include "ft_ls_options.h"

typedef struct	s_ls_file
{
	int			inode;
	int			block_size;
	char		*permissions;
	char		links;
	char		*user_id;
	char		*group_id;
	long long	size;
	char		*date;
	char		*name;
	t_error		e;
}				t_ls_file;

typedef struct	s_ls_context
{
	uint16_t	flag;
	int			(*compare)();
	t_rbtree	*files;
	t_path		*path;
	t_dstring	*printer;
	t_error		e;
}				t_ls_context;

int				parse_input(t_ls_context *c, char **data, int len);

int				parse_ls_file(char *name, char *dir_prefix, uint16_t flag);
int				set_ls_dir_data(t_ls_file **d, char *name, char *dir_prefix);
int				set_ls_file_data(uint16_t flag, t_ls_file **f,
		char *name, char *dir_prefix);

void			ft_ls(t_rbtree *files, t_path *path,
		t_dstring *printer, uint16_t flag);

#endif
