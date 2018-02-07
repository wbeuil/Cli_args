#include "cli_args.h"

static int			isNumber(char *str)
{
	int				i;

	if (!str)
		return (0);
	i = 0;
	if (str[0] == '-')
		i++;
	while (str[i])
	{
		if (!isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static void			error(t_arg args, int code)
{
	if (code == 1)
		fprintf(stderr, "error: %u type is not defined\n", args.optionsDef->type);
	else if (code == 2)
		fprintf(stderr, "error: Unknown option: %s\n", args.argv[args.i]);
	else if (code == 3)
		fprintf(stderr, "error: Unknown value: %s\n", args.argv[args.i]);
	exit(1);
}

void				freeOptions(t_opt **options)
{
	if ((*options)->next)
		freeOptions(&(*options)->next);
	if ((*options)->value)
		free((*options)->value);
	free(*options);
}

static int			hasDuplicates(t_opt **options, t_opt *new)
{
	t_opt			*opt;

	opt = *options;
	while (opt)
	{
		if (opt->name == new->name)
			return (1);
		opt = opt->next;	
	}
	return (0);
}

void				printOptions(t_opt **options)
{
	t_opt			*opt;

	opt = *options;
	while (opt)
	{
		printf("%s: %d\n", opt->name, *(int *)opt->value);
		opt = opt->next;
	}
}

static size_t		lengthOptions(t_opt **options)
{
	size_t			i;
	t_opt			*opt;

	i = 0;
	opt = *options;
	while (opt)
	{
		i++;
		opt = opt->next;
	}
	return (i);
}

static void			nextOption(t_opt **options, t_opt *new)
{
	t_opt			*opt;

	if (hasDuplicates(options, new))
	{
		fprintf(stderr, "error: Singular option already set [%s]\n", new->name);
		freeOptions(options);
		freeOptions(&new);
		exit(1);
	}
	opt = *options;
	while (opt->next)
		opt = opt->next;
	opt->next = new;
}

static t_opt		*getOption(t_arg args, t_def *optionsDef)
{
	t_opt			*options;
	int				length;
	int				j;
	int				k;

	if (!(options = (t_opt *)malloc(sizeof(*options))))
		return (NULL);
	options->name = optionsDef->name;
	length = 0;
	if (optionsDef->type == OPT_BOOLEAN)
	{
		if (!(options->value = (int *)malloc(sizeof(int))))
			return (NULL);
		*(int *)options->value = 1;
	}
	else if (optionsDef->type == OPT_INTEGER)
	{
		j = args.i;
		while (isNumber(args.argv[++j]))
			length++;
		printf("length: %d\n", length);
		if (!(options->value = (int *)malloc(sizeof(int) * (length))))
			return (NULL);
		j = args.i;
		k = 0;
		printf("lol\n");
		while (k < length)
		{
			++j;
			printf("arg: %s k: %d\n", args.argv[j], k);
			*(int *)options[k].value = atoi(args.argv[j]);
			k++;
		}
		printf("lol\n");
		k = 0;
		while (*(int *)options[k].value)
		{
			printf("number: %d\n", *(int *)options[k].value);
			k++;
		}
	}
	options->next = NULL;
	return (options);
}

static int			parseLongOptions(t_arg args, t_opt **options)
{
	size_t			i;
	t_opt			*tmp;
	t_def			*def;

	i = -1;
	def = args.optionsDef;
	while (++i < args.len)
	{
		tmp = getOption(args, def);
		if (tmp && strcmp(args.argv[args.i] + 2, def->name) == 0)
		{
			lengthOptions(options) > 0 ? nextOption(options, tmp) : (*options = tmp);
			break ;
		}
		freeOptions(&tmp);
		def++;
	}
	if (i == args.len)
		error(args, 2);
	return (1);
}

static int			parseShortOptions(t_arg args, t_opt **options)
{
	int				i;
	size_t			j;
	t_opt			*tmp;
	t_def			*def;

	i = 0;
	while (args.argv[args.i][++i])
	{
		j = -1;
		def = args.optionsDef;
		while (++j < args.len)
		{
			tmp = getOption(args, def);
			// args.i += 3;
			if (tmp && args.argv[args.i][i] == def->alias)
			{
				lengthOptions(options) > 0 ? nextOption(options, tmp) : (*options = tmp);
				break ;
			}
			freeOptions(&tmp);
			def++;
		}
		if (j == args.len)
		{
			fprintf(stderr, "error: Unknown option: -%c\n", args.argv[args.i][i]);
			exit(1);
		}
	}
	return (1);
}

static int			checkOptionType(t_arg args)
{
	size_t			i;
	t_type			type;

	i = -1;
	while (++i < args.len)
	{
		type = OPT_BOOLEAN;
		while (type <= OPT_INTEGER)
		{
			if (type == args.optionsDef->type)
				return (1);
			type++;
		}
		args.optionsDef++;
	}
	return (0);
}

t_opt				*commandLineArgs(t_arg args)
{
	t_opt			*options;

	options = NULL;
	if (args.argc > 1)
	{
		args.i = 0;
		while (args.argv[++args.i])
		{
			printf("next args.i 2: %d\n", args.i);
			if (!checkOptionType(args))
				error(args, 1);
			if (args.argv[args.i][0] != '-')
				error(args, 3);
			else if (!args.argv[args.i][1])
				error(args, 2);
			else if (args.argv[args.i][1] != '-')
				parseShortOptions(args, &options);
			else if (!args.argv[args.i][2])
				error(args, 2);
			else
				parseLongOptions(args, &options);
		}
	}
	return (options);
}

t_arg				initArguments(int argc, char **argv, t_def *optionsDef, size_t len)
{
	t_arg			args;

	args.argc = argc;
	args.argv = argv;
	args.optionsDef = optionsDef;
	args.len = len;
	args.i = 0;
	return (args);
}

