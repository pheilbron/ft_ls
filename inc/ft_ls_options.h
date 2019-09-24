/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_options.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 15:52:06 by pheilbro          #+#    #+#             */
/*   Updated: 2019/09/24 11:44:42 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_OPTIONS_H
# define FT_LS_OPTIONS_H

// FORMAT: (1/l/m/G overwrite eachother, C/x overwrite eachother, q is sep)
# define _1 3
# define _CAP_C 0b100
# define _CAP_G 0
# define _L 1
# define _M 2
# define _X 0b1100
# define _Q 0b10000

# define FORMAT 0b11111
 
//  SORT: (S/c/f/t/y/N overwrite eachother, r is sep)
# define _CAP_S 1 < 6
# define _C 2 < 6
# define _F 3 < 6
# define _R 8 < 6
# define _T 4 < 6
# define _U 5 < 6
# define _CAP_N 0

// FILTER: (
# define _CAP_A
# define _CAP_F
# define _CAP_T
# define _A
# define _D
# define _G
# define _H
# define _I
# define _N
# define _O
# define _S
# define _@

# define _CAP_R
# define _CAP_Y

typedef struct	s_option
{
	char		type;
	uint16_t	flag;
	uint16_t	mask;
	char		*long_op;
	char		*prefix;
}				t_option;

extern t_option	g_options_tab[];

#endif
