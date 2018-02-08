/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli_args.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <wbeuil@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 15:05:25 by William           #+#    #+#             */
/*   Updated: 2018/02/08 18:09:36 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLI_ARGS_H
# define CLI_ARGS_H

# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <ctype.h>

/*
** Enum and Structures
*/

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
	int					multiple;
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

/*
** Main function
*/

t_opt					*command_line_args(t_arg args);

/*
** Options functions
*/

t_opt					*get_option(t_arg args, t_def *options_def);
void					next_option(t_opt **options, t_opt *new);
t_opt					*unknown_option(t_arg args, t_opt **options);

/*
** Utilities functions
*/

int						is_number(char *str);
int						is_option(char *str);
int						has_duplicates(t_opt **options, t_opt *new);
size_t					length_options(t_opt **options);
int						check_option_type(t_arg args);

/*
** Argv functions
*/

char					**sort_argv(char **argv);

/*
** Struct functions
*/

t_arg					init_args(char **argv, t_def *options_def, size_t len);
void					free_argv(char **argv);
t_def					init_def(char *name, char alias, t_type type, char *description);
void					free_options(t_opt **options);
void					print_options(t_opt **options);

#endif
