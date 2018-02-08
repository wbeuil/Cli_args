/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <wbeuil@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 15:05:15 by William           #+#    #+#             */
/*   Updated: 2018/02/08 15:50:51 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cli_args.h"

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

t_arg				init_args(char **argv, t_def *options_def, size_t len)
{
	t_arg			args;

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
	def.multiple = 0;
	def.description = description;
	return (def);
}
