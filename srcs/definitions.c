/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   definitions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <wbeuil@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 11:52:34 by William           #+#    #+#             */
/*   Updated: 2018/02/12 16:23:55 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cli_args.h"
#include <string.h>
#include <stdio.h>

/*
** Add a definition variable.
*/

t_def				add_def(char *name, char *alias, t_type type, char *description)
{
	t_def			def;

	def.name = name;
	def.alias = alias;
	def.type = type;
	def.multiple = 0;
	def.description = description;
	return (def);
}

/*
** Print depending on the return code the associated definition error.
*/

void				definition_error(t_arg *args, int code)
{
	if (code == -1)
		fprintf(stderr, "error: Invalid option definitions: the name property is required on each definition\n");
	else if (code == -2)
		fprintf(stderr, "error: Invalid option definitions: to avoid ambiguity an alias cannot be numeric\n");
	else if (code == -3)
		fprintf(stderr, "error: Invalid option definitions: an alias must be a single character\n");
	else if (code == -4)
		fprintf(stderr, "error: Invalid option definitions: an alias cannot be '-'\n");
	else if (code == -5)
		fprintf(stderr, "error: Two or more option definitions have the same name\n");
	else if (code == -6)
		fprintf(stderr, "error: Two or more option definitions have the same alias\n");
	free_args(args);
	exit(1);
}

/*
** Verify if there is more than one defitions with the same alias.
*/

static int			has_same_alias(t_def *options_def, size_t size, size_t index)
{
	t_def			def;

	def = options_def[index];
	while (++index < size)
	{
		if (strcmp(def.alias, options_def[index].alias) == 0)
			return (1);
	}
	return (0);
}

/*
** Verify if there is more than one defitions with the same name.
*/

static int			has_same_name(t_def *options_def, size_t size, size_t index)
{
	t_def			def;

	def = options_def[index];
	while (++index < size)
	{
		if (strcmp(def.name, options_def[index].name) == 0)
			return (1);
	}
	return (0);
}

/*
** Check the options definitions variable for possible errors.
*/

int					check_definitions(t_def *options_def, size_t size)
{
	size_t			i;

	i = -1;
	while (++i < size)
	{
		if (!options_def[i].name
			|| (options_def[i].name && strlen(options_def[i].name) == 0))
			return (-1);
		if (options_def[i].alias && strlen(options_def[i].alias) != 0
			&& is_number(options_def[i].alias))
			return (-2);
		if (options_def[i].alias && strlen(options_def[i].alias) != 1)
			return (-3);
		if (options_def[i].alias && strcmp(options_def[i].alias, "-") == 0)
			return (-4);
		if (has_same_name(options_def, size, i))
			return (-5);
		if (options_def[i].alias && has_same_alias(options_def, size, i))
			return (-6);
	}
	return (1);
}