/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usage.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 18:26:52 by pheilbro          #+#    #+#             */
/*   Updated: 2019/09/09 19:35:13 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "ft_ls_options.h"

static char	*get_options(void)
{
	t_dstring	*s;
	int			i;

	s = ft_dstr_init();
	i = 0;
	while (g_options_tab[i].type)
		ft_dstr_add(s, &g_options_tab[i++].type, 1);
	return (ft_dstr_release(s));
}

void		print_usage(void)
{
	char	*options;
	ft_printf("usage: ls [-%s] [file ...]", options = get_options());
	free(options);
}
