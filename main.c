/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <William@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 11:53:13 by wbeuil            #+#    #+#             */
/*   Updated: 2018/02/08 00:10:04 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cli_args.h"

int					main(int argc, char **argv)
{
	t_arg			args;
	t_def			options_def[4];
	t_opt			*options;

	options_def[0] = init_def("help", 'h', OPT_BOOLEAN, "Display this usage guide.");
	options_def[1] = init_def("color", 'c', OPT_BOOLEAN, "Display the results in color.");
	options_def[2] = init_def("file", 'f', OPT_STRING, "Enter timeout.");
	options_def[3] = init_def("timeout", 't', OPT_INTEGER, "Enter timeout.");
	args = init_args(argc, argv, options_def, sizeof(options_def) / sizeof(options_def[0]));
	args.partial = 1;
	options = command_line_args(args);
	print_options(&options);
	free_options(&options);
	return (0);
}
