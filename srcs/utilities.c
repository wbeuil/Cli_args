/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <wbeuil@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 14:58:36 by William           #+#    #+#             */
/*   Updated: 2018/02/08 17:11:25 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cli_args.h"

int					is_number(char *str)
{
	int				i;

	if (!str)
		return (0);
	i = 0;
	if (str[0] == '-')
		i++;
	while (str[i])
	{
		if (!isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int					is_option(char *str)
{
	if (!str)
		return (0);
	else if (str && str[0] == '-' && str[1] != '-')
		return (1);
	else if (str && str[0] == '-' && str[1] == '-')
		return (2);
	return (0);
}

int					has_duplicates(t_opt **options, t_opt *new)
{
	t_opt			*opt;

	opt = *options;
	while (opt)
	{
		if (opt->name == new->name)
			return (1);
		opt = opt->next;
	}
	return (0);
}

size_t				length_options(t_opt **options)
{
	size_t			i;
	t_opt			*opt;

	i = 0;
	opt = *options;
	while (opt)
	{
		i++;
		opt = opt->next;
	}
	return (i);
}
