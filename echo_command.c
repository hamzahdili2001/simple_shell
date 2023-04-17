#include "shell.h"
#include <unistd.h>


void echo_command(char **args)
{
	int i , no_newline = 0;
	char *arg, *var_name, *var_value;


	if (args[1] != NULL && strcmp(args[1], "-n") == 0)
	{
		no_newline = 1;
		args++;
	}

	for (i = 1; args[i] != NULL; i++)
	{
		arg = args[i];

		if (strcmp(arg, "$?") == 0)
		{
			printf("%d", last_exit_status);
		}
		else if (strcmp(arg, "$$") == 0)
		{
			printf("%d", getpid());
		}
		else if (arg[0] == '$')
		{
			var_name = arg + 1;
			var_value = getenv(var_name);
			if (var_value != NULL)
			{
				 printf("%s", var_value);
			}
		}
		else
		{
			printf("%s", arg);
		}

		if (args[i + 1] != NULL)
		{
			printf(" ");
		}
	}

	if (!no_newline)
	{
		printf("\n");
	}
}
