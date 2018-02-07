/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <William@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 11:53:32 by wbeuil            #+#    #+#             */
/*   Updated: 2018/02/08 00:46:53 by William          ###   ########.fr       */
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

static int			is_option(char *str)
{
	if (!str || str[0] == '-')
		return (1);
	return (0);
}

static t_opt		*unknown_option(t_arg args, t_opt **options)
{
	t_opt			*opt;

	opt = *options;
	while (opt)
	{
		if (strcmp(opt->name,"_unknown") == 0)
			return (opt);
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
	return (opt);
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
	int				i;

	opt = *options;
	printf("{ ");
	while (opt)
	{
		i = -1;
		printf("%s: ", opt->name);
		if (opt->type == OPT_BOOLEAN)
			printf("true");
		else
		{
			printf("[");
			while (++i < opt->len)
			{
				if (opt->type == OPT_INTEGER)
					printf(" %d", ((int *)opt->value)[i]);
				else if (opt->type == OPT_STRING)
					printf(" '%s'", ((char **)opt->value)[i]);
				i == opt->len - 1 ? printf(" ") : printf(",");
			}
			printf("]");
		}
		opt = opt->next;
		if (opt)
			printf(", ");
	}
	printf(" }\n");
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

static t_arg		error(t_arg args, t_opt **options, int code)
{
	if (!args.partial)
	{
		if (code == 1)
			fprintf(stderr, "error: %u type is not defined\n", args.options_def->type);
		else if (code == 2)
			fprintf(stderr, "error: Unknown option: %s\n", args.argv[args.i]);
		else if (code == 3)
			fprintf(stderr, "error: Unknown value: %s\n", args.argv[args.i]);
		exit(1);
	}
	*options = unknown_option(args, options);
	return (args);
}

static t_opt		*get_option(t_arg args, t_def *options_def)
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
		while (is_number(args.argv[++k]))
			len++;
		if (!(options->value = (int *)malloc(sizeof(int) * len)))
			return (NULL);
		k = -1;
		while (++k < len)
			((int *)options->value)[k] = atoi(args.argv[args.i + k + 1]);
	}
	else if (options_def->type == OPT_STRING)
	{
		k = args.i;
		while (!is_option(args.argv[++k]))
			len++;
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
		tmp = get_option(args, def);
		if (tmp && strcmp(args.argv[index] + 2, def->name) == 0)
		{
			length_options(options) > 0 ? next_option(options, tmp) : (*options = tmp);
			args.i += tmp->len;
			break ;
		}
		free_options(&tmp);
		def++;
	}
	if (i == args.len)
		args = error(args, options, 2);
	return (args);
}

static t_arg		parse_short_options(t_arg args, t_opt **options)
{
	int				i;
	int				index;
	size_t			j;
	t_opt			*tmp;
	t_def			*def;

	i = 0;
	index = args.i;
	while (args.argv[index][++i])
	{
		j = -1;
		def = args.options_def;
		while (++j < args.len)
		{
			tmp = get_option(args, def);
			if (tmp && args.argv[index][i] == def->alias)
			{
				length_options(options) > 0 ? next_option(options, tmp) : (*options = tmp);
				args.i += tmp->len;
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
	return (args);
}

static int			check_option_type(t_arg args)
{
	size_t			i;
	t_type			type;

	i = -1;
	while (++i < args.len)
	{
		type = OPT_BOOLEAN;
		while (type <= OPT_STRING)
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
			if (!check_option_type(args))
				args = error(args, &options, 1);
			if (args.argv[args.i][0] != '-')
				args = error(args, &options, 3);
			else if (!args.argv[args.i][1])
				args = error(args, &options, 2);
			else if (args.argv[args.i][1] != '-')
				args = parse_short_options(args, &options);
			else if (!args.argv[args.i][2])
				args = error(args, &options, 2);
			else
				args = parse_long_options(args, &options);
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
	args.partial = 0;
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
