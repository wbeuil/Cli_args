#ifndef CLI_ARGS_H
# define CLI_ARGS_H

# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <ctype.h>

typedef enum			e_type
{
    OPT_BOOLEAN,
    OPT_INTEGER
}						t_type;

typedef struct			s_def
{
	char				*name;
	char				alias;
	enum e_type 		type;
	char				*description;
}						t_def;

typedef struct			s_opt
{
	char				*name;
	void				*value;
	struct s_opt		*next;
}						t_opt;

typedef struct			s_arg
{
	int					argc;
	char				**argv;
	struct s_def		*optionsDef;
	size_t				len;
	int					i;
}						t_arg;

t_arg					initArguments(int argc, char **argv, t_def *optionsDef, size_t len);
t_opt					*commandLineArgs(t_arg args);
void					freeOptions(t_opt **options);
void					printOptions(t_opt **options);

#endif