/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   example.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <wbeuil@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 15:12:20 by William           #+#    #+#             */
/*   Updated: 2018/02/22 20:50:26 by William          ###   ########.fr       */
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
	t_def			*option_defs;
	t_opt			*options;
	size_t			size;

	if (argc > 1)
	{
		size = 3;
		option_defs = init_option_defs(size);
		option_defs[0] = add_def("help", "h", OPT_BOOLEAN);
		option_defs[1] = add_def("file", "f", OPT_STRING);
		option_defs[1].multiple = 1;
		option_defs[2] = add_def("timeout", "t", OPT_INTEGER);
		args = init_args(argv, option_defs, size);
		args->partial = 1;
		options = command_line_args(args);
		print_options(&options);
		free_options(&options);
		free_args(args);
	}
	return (0);
}
