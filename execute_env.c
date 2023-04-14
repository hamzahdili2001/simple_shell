#include "shell.h"

void execute_env(void)
{
	extern char **environ;
	char **envptr = environ;

	while (*envptr != NULL)
	{
		write(STDOUT_FILENO, *envptr, _strlen(*envptr));
		write(STDOUT_FILENO, "\n", 1);
		envptr++;
	}
}
