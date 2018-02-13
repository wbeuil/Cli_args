/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <wbeuil@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 15:05:15 by William           #+#    #+#             */
/*   Updated: 2018/02/12 21:58:57 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cli_args.h"

/*
** Free all argv variables.
*/

void				free_argv(char **argv)
{
	int				i;

	if (!argv)
		return ;
	i = -1;
	while (argv[++i])
		free(argv[i]);
	free(argv);
}

/*
** Free each option and its value whithin the options variable.
*/

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

/*
** Before freeig the argument variable, we need to free
** the input arguments (argv) and the options' definitions.
*/

void				free_args(t_arg *args)
{
	if (args)
	{
		if (args->argv)
			free_argv(args->argv);
		if (args->option_defs)
			free(args->option_defs);
		free(args);
	}
}
