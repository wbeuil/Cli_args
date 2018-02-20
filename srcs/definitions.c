/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   definitions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <wbeuil@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 11:52:34 by William           #+#    #+#             */
/*   Updated: 2018/02/14 12:19:23 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cli_args.h"
#include <string.h>

/*
** Verify if the option definitions array has the right number
** of definitions.
*/

static int			is_full(t_def *option_defs, size_t size)
{
	size_t			i;

	i = -1;
	while (++i < size)
	{
		if (option_defs[i].type == OPT_INIT)
			return (0);
	}
	return (1);
}

/*
** Verifify if the definition option has a defined type property.
*/

static int			has_type(t_def def)
{
	t_type			type;

	type = OPT_BOOLEAN;
	while (type <= OPT_STRING)
	{
		if (def.type == type)
			return (1);
		type++;
	}
	return (0);
}

/*
** Verify if there is more than one defitions with the same alias.
*/

static int			has_same_alias(t_def *option_defs, size_t size, size_t index)
{
	t_def			def;

	def = option_defs[index];
	while (++index < size)
	{
		if (strcmp(def.alias, option_defs[index].alias) == 0)
			return (1);
	}
	return (0);
}

/*
** Verify if there is more than one defitions with the same name.
*/

static int			has_same_name(t_def *option_defs, size_t size, size_t index)
{
	t_def			def;

	def = option_defs[index];
	while (++index < size)
	{
		if (strcmp(def.name, option_defs[index].name) == 0)
			return (1);
	}
	return (0);
}

/*
** Check the options definitions variable for possible errors.
*/

int					check_definitions(t_def *option_defs, size_t size)
{
	size_t			i;

	if (!is_full(option_defs, size))
		return (-8);
	i = -1;
	while (++i < size)
	{
		if (!option_defs[i].name
			|| (option_defs[i].name && strlen(option_defs[i].name) == 0))
			return (-1);
		if (option_defs[i].alias && strlen(option_defs[i].alias) != 0
			&& is_number(option_defs[i].alias))
			return (-2);
		if (option_defs[i].alias && strlen(option_defs[i].alias) != 1)
			return (-3);
		if (option_defs[i].alias && strcmp(option_defs[i].alias, "-") == 0)
			return (-4);
		if (has_same_name(option_defs, size, i))
			return (-5);
		if (option_defs[i].alias && has_same_alias(option_defs, size, i))
			return (-6);
		if (!option_defs[i].type || !has_type(option_defs[i]))
			return (-7);
	}
	return (1);
}