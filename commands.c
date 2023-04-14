#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void cd_command(char **args)
{
	if (args[1] == NULL)
	{
		write(STDERR_FILENO, "cd: expected argument to \"cd\"\n",
				_strlen("cd: expected argument to \"cd\"\n"));
	}
	else
	{
		if (chdir(args[1]) != 0)
			perror("cd");
	}
}

void exit_command(char **args)
{
	if (args[1] == NULL)
		perror("exit");
	else
		exit(EXIT_SUCCESS); 
}

void env_command(char **args)
{
	extern char **environ;
	char **envptr = environ;

	(void)args;

	while (*envptr != NULL)
	{
		write(STDOUT_FILENO, *envptr, _strlen(*envptr));
		write(STDOUT_FILENO, "\n", 1);
		envptr++;
	}

}

void clear_command(char **args)
{
	(void)args;
	// TODO: change the setenv and make it run on any machine
	// FIX: Not working Well Yet
	setenv("TERM", "xterm", 1);
	write(STDERR_FILENO, "\033[2J", _strlen("\033[2J"));
	fflush(stdout);
}
