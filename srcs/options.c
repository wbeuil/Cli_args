/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <wbeuil@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 15:03:38 by William           #+#    #+#             */
/*   Updated: 2018/02/08 15:50:52 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cli_args.h"

t_opt				*unknown_option(t_arg args, t_opt **options)
{
	t_opt			*opt;

	opt = *options;
	while (opt)
	{
		if (strcmp(opt->name, "_unknown") == 0)
		{
			opt->value = (char **)realloc(opt->value, sizeof(char *) * (opt->len + 2));
			if (opt->value)
			{
				((char **)opt->value)[opt->len] = args.argv[args.i];
				((char **)opt->value)[opt->len + 1] = NULL;
			}
			opt->len++;
			return (*options);
		}
		opt = opt->next;
	}
	opt = (t_opt *)malloc(sizeof(*opt));
	if (opt)
	{
		opt->name = "_unknown";
		opt->type = OPT_STRING;
		opt->value = (char **)malloc(sizeof(char *) * 2);
		if (opt->value)
		{
			((char **)opt->value)[0] = args.argv[args.i];
			((char **)opt->value)[1] = NULL;
		}
		opt->len = 1;
		opt->next = NULL;
	}
	length_options(options) > 0 ? next_option(options, opt) : (*options = opt);
	return (*options);
}

void				next_option(t_opt **options, t_opt *new)
{
	t_opt			*opt;

	if (has_duplicates(options, new) && strcmp(new->name,"_unknown"))
	{
		fprintf(stderr, "error: Singular option already set [%s]\n", new->name);
		free_options(options);
		free_options(&new);
		exit(1);
	}
	opt = *options;
	while (opt->next)
		opt = opt->next;
	opt->next = new;
}

t_opt				*get_option(t_arg args, t_def *options_def)
{
	t_opt			*options;
	int				len;
	int				k;

	if (!(options = (t_opt *)malloc(sizeof(*options))))
		return (NULL);
	options->name = options_def->name;
	options->type = options_def->type;
	len = 0;
	if (options_def->type == OPT_BOOLEAN)
	{
		if (!(options->value = (int *)malloc(sizeof(int))))
			return (NULL);
		*(int *)options->value = 1;
	}
	else if (options_def->type == OPT_INTEGER)
	{
		k = args.i;
		while (args.argv[++k] && is_number(args.argv[k]))
			len++;
		if (!options_def->multiple)
			len = 1;
		if (!(options->value = (int *)malloc(sizeof(int) * len)))
			return (NULL);
		k = -1;
		while (++k < len)
			((int *)options->value)[k] = atoi(args.argv[args.i + k + 1]);
	}
	else if (options_def->type == OPT_STRING)
	{
		k = args.i;
		while (args.argv[++k] && !is_option(args.argv[k]))
			len++;
		if (!options_def->multiple)
			len = 1;
		if (!(options->value = (char **)malloc(sizeof(char *) * (len + 1))))
			return (NULL);
		((char **)options->value)[len] = NULL;
		k = -1;
		while (++k < len)
			((char **)options->value)[k] = args.argv[args.i + k + 1];
	}
	options->len = len;
	options->next = NULL;
	return (options);
}