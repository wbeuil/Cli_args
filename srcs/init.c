/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <wbeuil@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 16:08:45 by William           #+#    #+#             */
/*   Updated: 2018/02/13 09:26:10 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cli_args.h"

/*
** Initialization of the option variable.
*/

t_opt				*init_options(char *name, t_type type, int multiple)
{
	t_opt			*opt;

	opt = (t_opt *)malloc(sizeof(*opt));
	opt->name = name;
	opt->type = type;
	opt->value = NULL;
	opt->size = 0;
	opt->multiple = multiple;
	opt->next = NULL;
	return (opt);
}

/*
** Initialization of the argument variable.
*/

t_arg				*init_args(char **argv, t_def *option_defs, size_t size)
{
	t_arg			*args;
	char			**sorting_argv;
	int				ret;

	args = (t_arg *)malloc(sizeof(*args));
	sorting_argv = sort_argv(argv);
	args->argv = sorting_argv;
	args->option_defs = option_defs;
	if ((ret = check_definitions(option_defs, size)) < 0)
		definition_error(args, ret);
	args->size = size;
	args->i = 0;
	args->partial = 0;
	return (args);
}

/*
** Initialization of the option definitions variable.
*/

t_def				*init_options_def(size_t size)
{
	t_def			*option_defs;

	option_defs = (t_def *)malloc(sizeof(*option_defs) * size);
	return (option_defs);
}
