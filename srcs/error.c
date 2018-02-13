/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <wbeuil@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 09:35:46 by William           #+#    #+#             */
/*   Updated: 2018/02/13 11:11:28 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cli_args.h"
#include <stdio.h>

/*
** Depending on the partial variable of the argument, either print an
** error or push the option into the unknown variable.
*/

t_arg				*error(t_arg *args, t_opt **options, int code)
{
	if (!args->partial)
	{
		if (code == 1)
			fprintf(stderr, "error: Unknown option: %s\n", args->argv[args->i]);
		else if (code == 2)
			fprintf(stderr, "error: Unknown value: %s\n", args->argv[args->i]);
		free_options(options);
		free_args(args);
		exit(EXIT_FAILURE);
	}
	if (!(*options = unknown_option(args, options)))
		return (NULL);
	return (args);
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
	else if (code == -7)
		fprintf(stderr, "error: Invalid option definitions: the type property is required on each definition\n");
	free_args(args);
	exit(EXIT_FAILURE);
}

/*
** Print an error message for the failure of memory allocation.
*/

void				fail_malloc(void)
{
	fprintf(stderr, "error: Failed to allocate memory\n");
	exit(EXIT_FAILURE);
}
