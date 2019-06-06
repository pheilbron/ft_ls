/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_options.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 15:52:06 by pheilbro          #+#    #+#             */
/*   Updated: 2019/06/06 15:52:17 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_OPTIONS_H
# define FT_LS_OPTIONS_H

typedef struct	s_options
{
	char	long_form;
	char	rev;
	char	rec;
	char	all;
	char	by_time;
	char	**files;
}				t_options;

typedef struct	s_set_op
{
	char	type;
	void	(*f)();
}				t_set_op;

//t_set_op	g_ls_options = {
//	{'R', &set_rec_option},
//	{'a', &set_all_option},
//	{'l', &set_long_form_option},
//	{'r', &set_rev_option},
//	{'t', &set_by_time_option}
//};

#endif
