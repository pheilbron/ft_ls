/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 11:39:16 by pheilbro          #+#    #+#             */
/*   Updated: 2019/09/25 11:48:28 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls_utils.h"

int	(*get_sort(uint16_t flag))(void *, void *)
{
	const struct s_sort	sort_tab[] = {
		{_CAP_S, &compare_size},
		{_C, &compare_change_time},
		{_F, &no_sort},
		{_T, &compare_modify_time},
		{_U, &compare_access_time},
		{_CAP_N, &compare_name},
		{0, &compare_name}};
	int	i;

	i = 0;
	while (sort_tab[i].flag)
	{
		if (IS_SET(flag, sort_tab[i].flag, SORT))
			return (sort_tab[i].f);
		i++;
	}
	return (sort_tab[i].f);
}
