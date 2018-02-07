/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbeuil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 11:53:32 by wbeuil            #+#    #+#             */
/*   Updated: 2018/02/07 11:53:34 by wbeuil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cli_args.h"

static int			is_number(char *str)
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

static void			error(t_arg args, int code)
{
	if (code == 1)
		fprintf(stderr, "error: %u type is not defined\n", args.options_def->type);
	else if (code == 2)
		fprintf(stderr, "error: Unknown option: %s\n", args.argv[args.i]);
	else if (code == 3)
		fprintf(stderr, "error: Unknown value: %s\n", args.argv[args.i]);
	exit(1);
}

void				free_options(t_opt **options)
{
	if (!options || !(*options))
		return ;
	if ((*options)->next)
		free_options(&(*options)->next);
	if ((*options)->value)
		free((*options)->value);
	free(*options);
}

static int			has_duplicates(t_opt **options, t_opt *new)
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

void				print_options(t_opt **options)
{
	t_opt			*opt;

	opt = *options;
	while (opt)
	{
		printf("%s: %d\n", opt->name, *(int *)opt->value);
		opt = opt->next;
	}
}

static size_t		length_options(t_opt **options)
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

static void			next_option(t_opt **options, t_opt *new)
{
	t_opt			*opt;

	if (has_duplicates(options, new))
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

static t_opt		*get_option(t_arg args, t_def *options_def)
{
	t_opt			*options;
	int				length;
	int				j;
	int				k;

	if (!(options = (t_opt *)malloc(sizeof(*options))))
		return (NULL);
	options->name = options_def->name;
	length = 0;
	if (options_def->type == OPT_BOOLEAN)
	{
		if (!(options->value = (int *)malloc(sizeof(int))))
			return (NULL);
		*(int *)options->value = 1;
	}
	else if (options_def->type == OPT_INTEGER)
	{
		j = args.i;
		while (is_number(args.argv[++j]))
			length++;
		printf("length: %d\n", length);
		if (!(options->value = (int *)malloc(sizeof(int) * (length))))
			return (NULL);
		j = args.i;
		k = 0;
		printf("lol\n");
		while (k < length)
		{
			++j;
			printf("arg: %s k: %d\n", args.argv[j], k);
			*(int *)options[k].value = atoi(args.argv[j]);
			printf("lol2\n");
			k++;
		}
		printf("lol3\n");
		k = 0;
		while (k < length)
		{
			printf("number: %d\n", *(int *)options[k].value);
			k++;
		}
	}
	options->next = NULL;
	return (options);
}

static int			parse_long_options(t_arg args, t_opt **options)
{
	size_t			i;
	t_opt			*tmp;
	t_def			*def;

	i = -1;
	def = args.options_def;
	while (++i < args.len)
	{
		tmp = get_option(args, def);
		if (tmp && strcmp(args.argv[args.i] + 2, def->name) == 0)
		{
			length_options(options) > 0 ? next_option(options, tmp) : (*options = tmp);
			break ;
		}
		free_options(&tmp);
		def++;
	}
	if (i == args.len)
		error(args, 2);
	return (1);
}

static int			parse_short_options(t_arg args, t_opt **options)
{
	int				i;
	size_t			j;
	t_opt			*tmp;
	t_def			*def;

	i = 0;
	while (args.argv[args.i][++i])
	{
		j = -1;
		def = args.options_def;
		while (++j < args.len)
		{
			tmp = get_option(args, def);
			if (tmp && args.argv[args.i][i] == def->alias)
			{
				length_options(options) > 0 ? next_option(options, tmp) : (*options = tmp);
				break ;
			}
			free_options(&tmp);
			def++;
		}
		if (j == args.len)
		{
			fprintf(stderr, "error: Unknown option: -%c\n", args.argv[args.i][i]);
			exit(1);
		}
	}
	return (1);
}

static int			check_option_type(t_arg args)
{
	size_t			i;
	t_type			type;

	i = -1;
	while (++i < args.len)
	{
		type = OPT_BOOLEAN;
		while (type <= OPT_INTEGER)
		{
			if (type == args.options_def->type)
				return (1);
			type++;
		}
		args.options_def++;
	}
	return (0);
}

t_opt				*command_line_args(t_arg args)
{
	t_opt			*options;

	options = NULL;
	if (args.argc > 1)
	{
		args.i = 0;
		while (args.argv[++args.i])
		{
			printf("next args.i 2: %d\n", args.i);
			if (!check_option_type(args))
				error(args, 1);
			if (args.argv[args.i][0] != '-')
				error(args, 3);
			else if (!args.argv[args.i][1])
				error(args, 2);
			else if (args.argv[args.i][1] != '-')
				parse_short_options(args, &options);
			else if (!args.argv[args.i][2])
				error(args, 2);
			else
				parse_long_options(args, &options);
		}
	}
	return (options);
}

t_arg				init_args(int argc, char **argv, t_def *options_def, size_t len)
{
	t_arg			args;

	args.argc = argc;
	args.argv = argv;
	args.options_def = options_def;
	args.len = len;
	args.i = 0;
	return (args);
}

t_def				init_def(char *name, char alias, t_type type, char *description)
{
	t_def			def;

	def.name = name;
	def.alias = alias;
	def.type = type;
	def.description = description;
	return (def);
}
