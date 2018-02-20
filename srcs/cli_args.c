/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <wbeuil@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 15:05:13 by William           #+#    #+#             */
/*   Updated: 2018/02/14 15:19:00 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/cli_args.h"
#include <string.h>

/*
** Parse command line arguments for long options and compare them
** with our options. If we find one, we push it into a new variable.
*/

static t_arg		*parse_long_options(t_arg *args, t_opt **options)
{
	size_t			i;
	int				index;
	t_opt			*tmp;
	t_def			*defs;

	i = -1;
	index = args->i;
	defs = args->option_defs;
	while (++i < args->size)
	{
		if (strcmp(args->argv[index] + 2, defs->name) == 0)
		{
			if (!(tmp = get_option(args, defs)))
				return (NULL);
			add_option(args, options, tmp);
			args->i += tmp->size;
			break ;
		}
		defs++;
	}
	if (i == args->size)
		args = error(args, options, 1);
	return (args);
}

/*
** Parse command line arguments for short options and compare them
** with our options. If we find one, we push it into a new variable.
*/

static t_arg		*parse_short_options(t_arg *args, t_opt **options)
{
	size_t			i;
	int				index;
	t_opt			*tmp;
	t_def			*defs;

	i = -1;
	index = args->i;
	defs = args->option_defs;
	while (++i < args->size)
	{
		if (defs->alias && args->argv[index][1] == defs->alias[0])
		{
			if (!(tmp = get_option(args, defs)))
				return (NULL);
			add_option(args, options, tmp);
			args->i += tmp->size;
			break ;
		}
		defs++;
	}
	if (i == args->size)
		args = error(args, options, 1);
	return (args);
}

/*
** Parse each command line arguments to find correct ones (-h or --help).
** If there is an error, either push it into an unknown variable or
** print an error.
*/

t_opt				*command_line_args(t_arg *args)
{
	t_opt			*options;

	options = NULL;
	while (args->argv[++args->i])
	{
		if (args->argv[args->i][0] != '-')
			args = error(args, &options, 2);
		else if (!args->argv[args->i][1])
			args = error(args, &options, 1);
		else if (args->argv[args->i][1] != '-')
			args = parse_short_options(args, &options);
		else if (!args->argv[args->i][2])
			args = error(args, &options, 1);
		else
			args = parse_long_options(args, &options);
		if (!args)
			fail_malloc();
	}
	free_args(args);
	return (options);
}
