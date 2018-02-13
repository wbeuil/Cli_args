/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   integer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <wbeuil@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 16:30:17 by William           #+#    #+#             */
/*   Updated: 2018/02/13 09:26:31 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cli_args.h"
#include <limits.h>
#include <stdio.h>

/*
** Find if the string represents an integer.
*/

static int			is_integer(char *str)
{
	long			nbr;

	if (is_number(str))
	{
		nbr = atol(str);
		if (nbr > INT_MAX || nbr < INT_MIN)
			return (0);
		return (1);
	}
	return (0);
}

/*
** Print all the values inside the array of integers.
*/

void				print_integer(t_opt *opt)
{
	size_t			i;

	i = -1;
	if (opt->multiple)
		printf("[");
	while (++i < opt->size)
	{
		if (opt->multiple)
			printf(" ");
		printf("%d", ((int *)opt->value)[i]);
		if (opt->multiple)
			i == opt->size - 1 ? printf(" ") : printf(",");
	}
	if (opt->multiple)
		printf("]");
	if (opt->size == 0 && !opt->multiple)
		printf("null");
}

/*
** Return the size of the array of integers.
*/

size_t				integer_size(t_arg *args, t_def *option_defs, t_opt **options)
{
	int				i;
	size_t			size;

	i = args->i;
	size = 0;
	while (args->argv[++i] && !is_option(args->argv[i]))
	{
		if (is_integer(args->argv[i]))
			size++;
		else if (!args->partial)
		{
			fprintf(stderr, "error: Not an integer: %s\n", args->argv[i]);
			free_options(options);
			free_args(args);
			exit(1);
		}
	}
	if (!option_defs->multiple && size > 1)
		size = 1;
	return (size);
}

/*
** Return an array of integers.
*/

int					*integer_value(t_arg *args, size_t size)
{
	int				*value;
	size_t			i;

	value = (int *)malloc(sizeof(*value) * size);
	i = -1;
	while (++i < size)
		value[i] = atoi(args->argv[args->i + 1 + i]);
	return (value);
}