/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli_args.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <William@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 11:53:39 by wbeuil            #+#    #+#             */
/*   Updated: 2018/02/07 22:11:58 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLI_ARGS_H
# define CLI_ARGS_H

# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <ctype.h>

typedef enum			e_type
{
	OPT_BOOLEAN,
	OPT_INTEGER,
	OPT_STRING
}						t_type;

typedef struct			s_def
{
	char				*name;
	char				alias;
	enum e_type			type;
	char				*description;
}						t_def;

typedef struct			s_opt
{
	char				*name;
	enum e_type			type;
	void				*value;
	int					len;
	struct s_opt		*next;
}						t_opt;

typedef struct			s_arg
{
	int					argc;
	char				**argv;
	struct s_def		*options_def;
	size_t				len;
	int					i;
	int					partial;
}						t_arg;

t_arg					init_args(int argc, char **argv, t_def *options_def, size_t len);
t_def					init_def(char *name, char alias, t_type type, char *description);
t_opt					*command_line_args(t_arg args);
void					free_options(t_opt **options);
void					print_options(t_opt **options);

#endif
