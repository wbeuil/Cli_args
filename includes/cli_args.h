/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli_args.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <wbeuil@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 15:05:25 by William           #+#    #+#             */
/*   Updated: 2018/02/13 10:10:02 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLI_ARGS_H
# define CLI_ARGS_H

#include <stdlib.h>

/*
** Enum and Structures
*/

typedef enum			e_type
{
	OPT_BOOLEAN	= 1,
	OPT_INTEGER	= 2,
	OPT_STRING	= 3
}						t_type;

typedef struct			s_def
{
	char				*name;
	char				*alias;
	enum e_type			type;
	int					multiple;
	char				*description;
}						t_def;

typedef struct			s_opt
{
	char				*name;
	enum e_type			type;
	void				*value;
	size_t				size;
	int					multiple;
	struct s_opt		*next;
}						t_opt;

typedef struct			s_arg
{
	int					argc;
	char				**argv;
	struct s_def		*option_defs;
	size_t				size;
	int					i;
	int					partial;
}						t_arg;

/*
** Main function
*/

t_opt					*command_line_args(t_arg *args);

/*
** Options definitions functions
*/

t_def					add_def(char *name, char *alias, t_type type, char *description);
int						check_definitions(t_def *option_defs, size_t size);

/*
** Init functions
*/

t_opt					*init_options(char *name, t_type type, int multiple);
t_arg					*init_args(char **argv, t_def *option_defs, size_t size);
t_def					*init_options_def(size_t size);

/*
** Free functions
*/

void					free_args(t_arg *args);
void					free_argv(char **argv);
void					free_options(t_opt **options);

/*
** Error functions
*/

t_arg					*error(t_arg *args, t_opt **options, int code);
void					definition_error(t_arg *args, int code);
void					fail_malloc(void);

/*
** Options functions
*/

t_opt					*get_option(t_arg *args, t_def *option_defs);
void					add_option(t_arg *args, t_opt **options, t_opt *new);
t_opt					*unknown_option(t_arg *args, t_opt **options);

/*
** Option type functions
*/

int						*boolean_value(void);
int						*integer_value(t_arg *args, size_t size);
size_t					integer_size(t_arg *args, t_def *option_defs, t_opt **options);
char					**string_value(t_arg *args, size_t size);
size_t					string_size(t_arg *args, t_def *option_defs);

/*
** Utilities functions
*/

int						is_number(char *str);
int						is_option(char *str);
int						has_duplicates(t_opt **options, t_opt *new);
size_t					length_options(t_opt **options);

/*
** Argv function
*/

char					**sort_argv(char **argv);

/*
** Print functions
*/

void					print_options(t_opt **options);
void					print_boolean(void);
void					print_integer(t_opt *opt);
void					print_string(t_opt *opt);

#endif
