/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 11:39:16 by pheilbro          #+#    #+#             */
/*   Updated: 2019/09/26 10:53:01 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "ft_ls_utils.h"

int	(*get_sort(uint32_t flag))(t_ls_file *, t_ls_file *)
{
	const struct s_sort	sort_tab[] = {
		{_CAP_S, &compare_size},
		{_C, &compare_time},
		{_F, &no_sort},
		{_T, &compare_time},
		{_U, &compare_time},
		{_CAP_N, &compare_name},
		{0, &compare_name}};
	int					i;

	i = 0;
	while (sort_tab[i].flag)
	{
		if (IS_SET(flag, sort_tab[i].flag, SORT))
			return (sort_tab[i].f);
		i++;
	}
	return (sort_tab[i].f);
}

void	(*process_print_strings(uint32_t flag))(t_dstring *, t_vector *)
{
	const struct s_printer	print_tab[] = {
		{_CAP_C, &format_vertical_grid},
		{_x, &format_horizontal_grid},
		{_GAP_G, &format_vertial_grid},
		{_G, &format_list},
		{_O, &format_list},
		{_L, &format_list},
		{_1, &format_list},
		{_M, &format_commas}};
	int						i;

	i = 0;
	while (print_tab[i].flag)
	{
		if (IS_SET(flag, print_tab[i].flag, FORMAT))
			return (print_tab[i].f);
		i++;
	}
	return (print_tab[i].f);
}
