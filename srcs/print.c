/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <wbeuil@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 16:07:24 by William           #+#    #+#             */
/*   Updated: 2018/02/09 21:00:35 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cli_args.h"
#include <stdio.h>

/*
** Print every option with a special template from the console.log of
** javascript: { help: true }.
*/

void				print_options(t_opt **options)
{
	t_opt			*opt;
	size_t			i;

	opt = *options;
	printf("{ ");
	while (opt)
	{
		i = -1;
		printf("%s: ", opt->name);
		if (opt->type == OPT_BOOLEAN)
			print_boolean();
		else if (opt->type == OPT_INTEGER)
			print_integer(opt);
		else if (opt->type == OPT_STRING)
			print_string(opt);
		opt = opt->next;
		if (opt)
			printf(", ");
	}
	printf(" }\n");
}