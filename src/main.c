/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 19:44:41 by pheilbro          #+#    #+#             */
/*   Updated: 2019/09/25 15:08:43 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "ft_error.h"

static t_ls_context	*init_ls_context(void)
{
	t_ls_context	*c;

	if (!(c = malloc(sizeof(*c))))
		return (NULL);
	if (!(c->files = malloc(sizeof(*(c->files)))))
		return (NULL);
	if (!(c->path = malloc(sizeof(*(c->path)))))
		return (NULL);
	if (!(c->printer = malloc(sizeof(*(c->printer)))))
		return (NULL);
	c->e.no = 0;
	c->e.data = NULL;
}

void				free_ls_context(t_ls_context *c)
{
	free(c->files);
	ft_dstr_free(printer);
	ft_dstr_free((t_dstring *)path);
	free(c);
}

int					main(int ac, char **av)
{
	t_ls_context	*c;

	if (!(c = init_ls_context()))
		write(1, "\n", 1);
	else if (parse_input(c, av + 1, ac - 1))
		ft_ls(c->files, c->path, c->printer, c->options);
	else
		ft_error_print_std_message("ft_ls", c->e);
	free_ls_context(c);
	return (0);
}
