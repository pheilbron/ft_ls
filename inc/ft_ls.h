/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 15:51:40 by pheilbro          #+#    #+#             */
/*   Updated: 2019/09/23 15:48:52 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS
# define FT_LS

# include "ft_ls_options.h"

typedef struct	s_ls_file
{
	char	*permissions;
	int		hard_links;
	char	*group_id;
	char	*user_id;
	int		size;
	struct tm	date;
	char	*name;
	t_error		e;
}				t_ls_file;

typedef struct	s_ls_dir
{
	struct dirent	*entry;
	t_error			e;
}				t_ls_dir;

typedef struct	s_ls_context
{
	uint16_t		flag;
	t_hash_table	*dirs;
	t_hash_table	*files;
	t_error		e;
}				t_ls_context;

int	parse_input(t_ls_context *c, char **data, int len);

#endif
