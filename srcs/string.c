/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <wbeuil@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 17:24:07 by William           #+#    #+#             */
/*   Updated: 2018/02/13 09:27:43 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cli_args.h"
#include <stdio.h>

/*
** Print all the values inside the array of strings.
*/

void				print_string(t_opt *opt)
{
	size_t			i;

	i = -1;
	if (opt->multiple)
		printf("[");
	while (++i < opt->size)
	{
		if (opt->multiple)
			printf(" ");
		printf("'%s'", ((char **)opt->value)[i]);
		if (opt->multiple)
			i == opt->size - 1 ? printf(" ") : printf(",");
	}
	if (opt->multiple)
		printf("]");
	if (opt->size == 0 && !opt->multiple)
		printf("null");
}

/*
** Return the size of the array of strings.
*/

size_t				string_size(t_arg *args, t_def *option_defs)
{
	int				i;
	size_t			size;

	i = args->i;
	size = 0;
	while (args->argv[++i] && !is_option(args->argv[i]))
		size++;
	if (!option_defs->multiple && size > 1)
		size = 1;
	return (size);
}

/*
** Return an array of strings.
*/

char				**string_value(t_arg *args, size_t size)
{
	char			**value;
	size_t			i;

	value = (char **)malloc(sizeof(*value) * (size + 1));
	value[size] = NULL;
	i = -1;
	while (++i < size)
		value[i] = args->argv[args->i + 1 + i];
	return (value);
}
