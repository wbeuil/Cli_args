/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <wbeuil@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 15:05:15 by William           #+#    #+#             */
/*   Updated: 2018/02/12 16:11:45 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cli_args.h"

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
	int				i;

	if (args)
	{
		if (args->argv)
		{
			i = -1;
			while (args->argv[++i])
				free(args->argv[i]);
			free(args->argv);
		}
		if (args->options_def)
			free(args->options_def);
		free(args);
	}
}
