#include "cli_args.h"
#include <stdio.h>

int					main(int argc, char **argv)
{
	static t_arg	args;
	t_def			optionsDef[] =
	{
		{"help", 'h', OPT_BOOLEAN, "Display this usage guide."},
		{"color", 'c', OPT_BOOLEAN, "Display the results in color."},
		{"timeout", 't', OPT_INTEGER, "LOL"}
	};
	t_opt			*options;

	args = initArguments(argc, argv, optionsDef, sizeof(optionsDef) / sizeof(optionsDef[0]));
	options = commandLineArgs(args);
	printOptions(&options);
	freeOptions(&options);
	return (0);
}