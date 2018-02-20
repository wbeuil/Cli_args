/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <wbeuil@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 16:08:45 by William           #+#    #+#             */
/*   Updated: 2018/02/16 11:30:36 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cli_args.h"

/*
** Initialization of the option variable.
*/

t_opt				*init_options(char *name, t_type type, int multiple)
{
	t_opt			*opt;

	if (!(opt = (t_opt *)malloc(sizeof(*opt))))
		return (NULL);
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
	if (!args || !sorting_argv)
		fail_malloc();
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

t_def				*init_option_defs(size_t size)
{
	t_def			*option_defs;
	size_t			i;

	if (!(option_defs = (t_def *)malloc(sizeof(*option_defs) * size)))
		fail_malloc();
	i = -1;
	while (++i < size)
		option_defs[i] = add_def(NULL, NULL, OPT_INIT);
	return (option_defs);
}

/*
** Add a definition variable.
*/

t_def				add_def(char *name, char *alias, t_type type)
{
	t_def			def;

	def.name = name;
	def.alias = alias;
	def.type = type;
	def.multiple = 0;
	def.description = NULL;
	def.label = NULL;
	return (def);
}
