/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <wbeuil@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 15:03:38 by William           #+#    #+#             */
/*   Updated: 2018/02/13 09:47:29 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cli_args.h"
#include <stdio.h>
#include <string.h>

/*
** Find any duplicates in the arguments and either print an error
** if there is one or create/add another variable option.
*/

void				add_option(t_arg *args, t_opt **options, t_opt *new)
{
	t_opt			*opt;

	if (options && *options && has_duplicates(options, new)
		&& strcmp(new->name, "_unknown"))
	{
		fprintf(stderr, "error: Singular option already set [%s]\n", new->name);
		free_options(options);
		free_options(&new);
		free_args(args);
		exit(EXIT_FAILURE);
	}
	if (length_options(options) > 0)
	{
		opt = *options;
		while (opt->next)
			opt = opt->next;
		opt->next = new;
	}
	else
		*options = new;
}

/*
** Instead of printing an error during the parsing, push the argument
** in the unknown variable when the partial parsing variable is on.
*/

t_opt				*unknown_option(t_arg *args, t_opt **options)
{
	t_opt			*opt;

	opt = *options;
	while (opt)
	{
		if (strcmp(opt->name, "_unknown") == 0)
		{
			opt->value = (char **)realloc(opt->value, sizeof(char *) * (opt->size + 2));
			((char **)opt->value)[opt->size] = args->argv[args->i];
			((char **)opt->value)[opt->size + 1] = NULL;
			opt->size++;
			return (*options);
		}
		opt = opt->next;
	}
	opt = init_options("_unknown", OPT_STRING, 1);
	opt->value = (char **)malloc(sizeof(char *) * 2);
	((char **)opt->value)[0] = args->argv[args->i];
	((char **)opt->value)[1] = NULL;
	opt->size = 1;
	add_option(args, options, opt);
	return (*options);
}

/*
** Initialize an option variable depending on its type
** (boolean, integer, string).
*/

t_opt				*get_option(t_arg *args, t_def *option_defs)
{
	t_opt			*options;
	size_t			size;

	options = init_options(option_defs->name, option_defs->type, option_defs->multiple);
	size = 0;
	if (options->type == OPT_BOOLEAN)
	{
		options->value = boolean_value();
	}
	else if (options->type == OPT_INTEGER)
	{
		size = integer_size(args, option_defs, &options);
		options->value = integer_value(args, size);
	}
	else if (options->type == OPT_STRING)
	{
		size = string_size(args, option_defs);
		options->value = string_value(args, size);
	}
	options->size = size;
	return (options);
}