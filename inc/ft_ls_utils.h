/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 11:48:39 by pheilbro          #+#    #+#             */
/*   Updated: 2019/09/25 11:50:08 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_UTILS_H
# define FT_LS_UTILS_H

struct	s_sort
{
	uint16_t	flag;
	int			(*f)();
};

int		(*get_sort(uint16_t flag))(void * void *);

#endif
