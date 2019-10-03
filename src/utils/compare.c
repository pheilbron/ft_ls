/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 19:01:09 by pheilbro          #+#    #+#             */
/*   Updated: 2019/10/03 14:22:50 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	compare_name(t_ls_file *a, t_ls_file *b)
{
	return (ft_strcmp(a->name, b->name));
}

int	compare_size(t_ls_file *a, t_ls_file *b)
{
	return (a->size - b->size);
}

int	compare_time(t_ls_file *a, t_ls_file *b)
{

}

int	no_sort(t_ls_file *a, t_ls_file *b)
{
	return (1);
}
