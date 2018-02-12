/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   example.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <wbeuil@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 15:12:20 by William           #+#    #+#             */
/*   Updated: 2018/02/12 16:36:49 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cli_args.h"

/*
** Initialize args and options variables before parsing commande line
** arguments.
*/

int					main(int argc, char **argv)
{
	t_arg			*args;
	t_def			*options_def;
	t_opt			*options;
	size_t			size;

	if (argc > 1)
	{
		size = 4;
		if (!(options_def = init_options_def(size)))
			fail_malloc();
		options_def[0] = add_def("help", "h", OPT_BOOLEAN, "Display this usage guide.");
		options_def[1] = add_def("color", "c", OPT_BOOLEAN, "Display the results in color.");
		options_def[2] = add_def("file", "f", OPT_STRING, "Enter timeout.");
		options_def[3] = add_def("timeout", "t", OPT_INTEGER, "Enter timeout.");
		options_def[3].multiple = 1;
		if (!(args = init_args(argv, options_def, size)))
			fail_malloc();
		args->partial = 1;
		options = command_line_args(args);
		print_options(&options);
		free_options(&options);
		free_args(args);
	}
	return (0);
}
