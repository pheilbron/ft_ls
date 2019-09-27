/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 15:51:40 by pheilbro          #+#    #+#             */
/*   Updated: 2019/09/26 12:37:44 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS
# define FT_LS

# include <stdint.h>
# include "ft_ls_options.h"
# include "ft_error.h"
# include "ft_rbtree.h"
# include "ft_dstring.h"

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

typedef struct	s_offsets
{
	uint8_t	max_inode_len;
	uint8_t	max_block_size_len;
	uint8_t	max_links_len;
	uint8_t	max_uid_len;
	uint8_t	max_gid_len;
	uint8_t	max_size_len;
}				t_offsets;

typedef struct	s_ls_context
{
	uint32_t	flag;
	int			(*compare)();
	t_path		*path;
	t_dstring	*printer;
	t_offsets	*offsets;
	t_error		e;
}				t_ls_context;

int				parse_input(t_ls_context *c, t_rbtree *files,
		char **data, int len);

int				parse_ls_file(char *name, char *dir_prefix, uint16_t flag);
int				set_ls_dir_data(t_ls_file **d, char *name, char *dir_prefix);
int				set_ls_file_data(uint16_t flag, t_ls_file **f,
		char *name, char *dir_prefix);

void			ft_ls(t_ls_context *c, t_rbtree *files);

#endif
