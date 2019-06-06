/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 15:51:11 by pheilbro          #+#    #+#             */
/*   Updated: 2019/06/06 15:51:15 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls_options.h"
#include "ft_ls.h"

int		set_option(t_options *ops, char option)
{
	int	i;

	i = 0;
	while (g_ls_options[i].type)
	{
		if (g_ls_options[i].type == option)
			return (g_ls_options[i].(*f)());
		i++;
	}
	return (0);
}

void	print_usage(void)
{
	printf("usage: ls [-");
	while (g_ls_options[i].type)
		printf("%c", g_ls_options[i++].type);
	printf("] [file ...]");
}

void	parse_input(char **options, int len, t_options *ops)
{
	int	is_valid;
	int	i;

	is_valid = 1;
	i = 0;
	while (i < len)
	{
		if (*options[i] == '-')
		{
			i++;
			while (*options[i] && set_option(*options[i]))
				i++;
			if 

void	parse_input(char *options, t_options *ops)
{
	int	is_valid;

	is_valid = 1;
	while (*options && is_valid)
	{
		if (*options == '-')
		{
			options++;
			while (*options && set_option(*options))
				options++;
			if (*options && (*options != ' ' || *(options - 1) == '-'))
				is_valid = 0;
			options++;
		}
		else
			is_valid = 0;
		options++;
	}
}
