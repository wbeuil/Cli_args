/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   example.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <wbeuil@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 15:12:20 by William           #+#    #+#             */
/*   Updated: 2018/02/08 18:40:51 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cli_args.h"

static t_arg		init_command_line_args(char **argv)
{
	t_arg			args;
	t_def			*options_def;
	char			**sorting_argv;
	size_t			len;

	len = 4;
	options_def = (t_def *)malloc(sizeof(*options_def) * len);
	sorting_argv = sort_argv(argv);
	options_def[0] = init_def("help", 'h', OPT_BOOLEAN, "Display this usage guide.");
	options_def[1] = init_def("color", 'c', OPT_BOOLEAN, "Display the results in color.");
	options_def[2] = init_def("file", 'f', OPT_STRING, "Enter timeout.");
	options_def[3] = init_def("timeout", 't', OPT_INTEGER, "Enter timeout.");
	args = init_args(sorting_argv, options_def, len);
	args.partial = 1;
	return (args);
}

int					main(int argc, char **argv)
{
	t_arg			args;
	t_opt			*options;

	if (argc > 1)
	{
		args = init_command_line_args(argv);
		options = command_line_args(args);
		print_options(&options);
		free_options(&options);
		free_argv(args.argv);
	}
	return (0);
}
