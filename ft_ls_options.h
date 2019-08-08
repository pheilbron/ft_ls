/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_options.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 15:52:06 by pheilbro          #+#    #+#             */
/*   Updated: 2019/08/08 13:47:24 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_OPTIONS_H
# define FT_LS_OPTIONS_H

# define LONG 1
# define REV 2
# define REC 4
# define TIME 8
# define ALL 15

typedef struct	s_options
{
	uint8_t	flags;
	char	**files;
}				t_options;

typedef struct	s_set_op
{
	char	type;
	void	(*f)();
}				t_set_op;

#endif
