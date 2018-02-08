/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <wbeuil@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 14:47:47 by William           #+#    #+#             */
/*   Updated: 2018/02/08 15:50:47 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cli_args.h"

void				free_argv(char **argv)
{
	int				i;

	i = -1;
	while (argv[++i])
		free(argv[i]);
	free(argv);
}

static char			**fill_argv(char **sort, char **argv)
{
	int				i;
	int				j;
	int				l;

	i = -1;
	l = 0;
	while (argv[++i])
	{
		if (is_option(argv[i]) == 1)
		{
			j = 0;
			while (argv[i][++j])
			{
				sort[i + l][1] = argv[i][j];
				if (argv[i][j + 1])
					l++;
			}
		}
		else
		{
			j = -1;
			while (argv[i][++j])
				sort[i + l][j] = argv[i][j];
		}
	}
	return (sort);
}

static char			**malloc_argv(char **sort, char **argv)
{
	int				i;
	int				j;
	int				k;
	int				l;

	i = -1;
	l = 0;
	while (argv[++i])
	{
		if (is_option(argv[i]) == 1)
		{
			j = 0;
			while (argv[i][++j])
			{
				if (!(sort[i + l] = (char *)malloc(sizeof(**sort) * 3)))
					return (NULL);
				sort[i + l][0] = '-';
				sort[i + l][2] = '\0';
				if (argv[i][j + 1])
					l++;
			}
		}
		else
		{
			j = -1;
			k = 0;
			while (argv[i][++j])
				k++;
			if (!(sort[i + l] = (char *)malloc(sizeof(**sort) * (k + 1))))
				return (NULL);
			sort[i + l][k] = '\0';
		}
	}
	return (sort);
}

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

char				**sort_argv(char **argv)
{
	int				count;
	char			**sort;

	count = count_argv(argv);
	if (!(sort = (char **)malloc(sizeof(*sort) * (count + 1))))
		return (NULL);
	sort[count] = NULL;
	if (!(sort = malloc_argv(sort, argv)))
		return (NULL);
	sort = fill_argv(sort, argv);
	return (sort);
}