/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <wbeuil@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 14:47:47 by William           #+#    #+#             */
/*   Updated: 2018/02/13 09:24:24 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cli_args.h"
#include <stdlib.h>
#include <string.h>

/*
** Fill the array of string with each input argument.
*/

static char			*init_str(int len, char *arg)
{
	int				i;
	char			*str;

	str = (char *)malloc(sizeof(*str) * (len + 1));
	str[len] = '\0';
	if (arg)
	{
		i = -1;
		while (arg[++i])
			str[i] = arg[i];
	}
	else
		str[0] = '-';
	return (str);
}

/*
** Count the number of characters of each input arguments and
** allocate memory inside the array of strings.
*/

static char			**malloc_argv(char **sort, char **argv)
{
	int				i;
	int				j;
	int				k;

	i = -1;
	k = 0;
	while (argv[++i])
	{
		if (is_option(argv[i]) == 1)
		{
			j = 0;
			while (argv[i][++j])
			{
				sort[i + k] = init_str(2, NULL);
				sort[i + k][1] = argv[i][j];
				if (argv[i][j + 1])
					k++;
			}
		}
		else
			sort[i + k] = init_str(strlen(argv[i]), argv[i]);
	}
	return (sort);
}

/*
** Count the number of input arguments given that if there are
** short options combined in one string we need to count each
** letter as an argument.
*/

static int			count_argv(char **argv)
{
	int				i;
	int				j;
	int				count;

	i = 0;
	count = 1;
	while (argv[++i])
	{
		if (is_option(argv[i]) == 1)
		{
			j = 0;
			while (argv[i][++j])
				count++;
		}
		else
			count++;
	}
	return (count);
}

/*
** Function to sort input arguments whithin a new array
** of strings. Useful for short options that are combined in
** a single string.
*/

char				**sort_argv(char **argv)
{
	int				count;
	char			**sort;

	count = count_argv(argv);
	sort = (char **)malloc(sizeof(*sort) * (count + 1));
	sort[count] = NULL;
	sort = malloc_argv(sort, argv);
	return (sort);
}
