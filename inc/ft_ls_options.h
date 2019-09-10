/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_options.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 15:52:06 by pheilbro          #+#    #+#             */
/*   Updated: 2019/09/09 19:36:20 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_OPTIONS_H
# define FT_LS_OPTIONS_H

# define _1 1
# define _CAP_C 2
# define _X 3
# define _L 4
# define _C 8
# define _U 16
# define _R 32
# define _T 64
# define _@ 128
# define _D 256
# define _E 512

# define DISPLAY_MASK 7
# define TIME_MASK 24

typedef struct	s_option
{
	char		type;
	uint16_t	flag;
	uint16_t	mask;
	char		*long_version;
}				t_option;

extern t_option	g_options_tab[];

#endif
