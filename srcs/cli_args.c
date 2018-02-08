/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <wbeuil@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 15:05:13 by William           #+#    #+#             */
/*   Updated: 2018/02/08 18:43:04 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cli_args.h"

static t_arg		error(t_arg args, t_opt **options, int code)
{
	if (!args.partial)
	{
		if (code == 1)
			fprintf(stderr, "error: Unknown option: %s\n", args.argv[args.i]);
		else if (code == 2)
			fprintf(stderr, "error: Unknown value: %s\n", args.argv[args.i]);
		exit(1);
	}
	*options = unknown_option(args, options);
	return (args);
}

static t_arg		parse_long_options(t_arg args, t_opt **options)
{
	size_t			i;
	int				index;
	t_opt			*tmp;
	t_def			*def;

	i = -1;
	index = args.i;
	def = args.options_def;
	while (++i < args.len)
	{
		if (strcmp(args.argv[index] + 2, def->name) == 0)
		{
			tmp = get_option(args, def);
			length_options(options) > 0 ? next_option(options, tmp) : (*options = tmp);
			args.i += tmp->len;
			break ;
		}
		def++;
	}
	if (i == args.len)
		args = error(args, options, 1);
	return (args);
}

static t_arg		parse_short_options(t_arg args, t_opt **options)
{
	size_t			i;
	int				index;
	t_opt			*tmp;
	t_def			*def;

	i = -1;
	index = args.i;
	def = args.options_def;
	while (++i < args.len)
	{
		if (args.argv[index][1] == def->alias)
		{
			tmp = get_option(args, def);
			length_options(options) > 0 ? next_option(options, tmp) : (*options = tmp);
			args.i += tmp->len;
			break ;
		}
		def++;
	}
	if (i == args.len)
		args = error(args, options, 1);
	return (args);
}

t_opt				*command_line_args(t_arg args)
{
	t_opt			*options;

	options = NULL;
	while (args.argv[++args.i])
	{
		if (args.argv[args.i][0] != '-')
			args = error(args, &options, 2);
		else if (!args.argv[args.i][1])
			args = error(args, &options, 1);
		else if (args.argv[args.i][1] != '-')
			args = parse_short_options(args, &options);
		else if (!args.argv[args.i][2])
			args = error(args, &options, 1);
		else
			args = parse_long_options(args, &options);
	}
	return (options);
}
