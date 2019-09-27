/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_options.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 15:52:06 by pheilbro          #+#    #+#             */
/*   Updated: 2019/09/26 09:36:19 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_OPTIONS_H
# define FT_LS_OPTIONS_H

// FORMAT: (1/l/m/G overwrite eachother, C/x overwrite eachother, q is sep)
# define _CAP_G 0
# define _L 1
# define _M 2
# define _1 3
# define _G 0b0100
# define _O 0b1000
# define _CAP_C 0b010000
# define _X 0b100000

# define _Q 0b1000000

# define FORMAT 0b1111
# define FORMAT_LONG 0b110000
 
//  SORT: (S/c/f/t/y/N overwrite eachother, r is sep)
# define _CAP_S 1 << 8
# define _C 2 << 8
# define _F 3 << 8
# define _R 8 << 8
# define _T 4 << 8
# define _U 5 << 8
# define _CAP_N 0

# define SORT 0b111 << 8

// FILTER: (
# define _CAP_A 1UL << 13
# define _CAP_F 1UL << 14
# define _CAP_T 1UL << 15
# define _A 1UL << 16
# define _D 1UL << 17
# define _H 1UL << 18
# define _I 1UL << 19
# define _N 1UL << 20
# define _S 1UL << 21
# define _AT 1UL << 22

# define _CAP_R 1UL << 23
# define _CAP_Y 1UL << 24

# define RECURSE 3UL << 23

# define IS_SET(flag, op, mask) ((flag & mask) == op ? 1 : 0)

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
