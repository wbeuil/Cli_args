/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   example.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <wbeuil@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 15:12:20 by William           #+#    #+#             */
/*   Updated: 2018/02/08 15:51:46 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cli_args.h"

int					main(int argc, char **argv)
{
	t_arg			args;
	t_def			options_def[4];
	t_opt			*options;
	char			**sorting_argv;

	if (argc > 1)
	{
		options_def[0] = init_def("help", 'h', OPT_BOOLEAN, "Display this usage guide.");
		options_def[1] = init_def("color", 'c', OPT_BOOLEAN, "Display the results in color.");
		options_def[2] = init_def("file", 'f', OPT_STRING, "Enter timeout.");
		options_def[3] = init_def("timeout", 't', OPT_INTEGER, "Enter timeout.");
		sorting_argv = sort_argv(argv);
		args = init_args(sorting_argv, options_def, sizeof(options_def) / sizeof(options_def[0]));
		args.partial = 1;
		options = command_line_args(args);
		print_options(&options);
		free_options(&options);
		free_argv(sorting_argv);
	}
	return (0);
}
