#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define PATH_SIZE 4096
void cd_command(char **args)
{
	char *dir;
	char old_pwd[PATH_SIZE];

	if (args[1] == NULL)
	{
		dir = getenv("HOME");
		if (dir == NULL)
		{
			perror("cd");
			return;
		}
	} 
	else if (_strcmp(args[1], "-") == 0)
	{
		dir = getenv("OLDPWD");
		if (dir == NULL)
		{
			perror("cd");
			return;
		}
	} 
	else 
	{
		dir = args[1];
	}

	if (getcwd(old_pwd, PATH_SIZE) == NULL)
	{
		perror("cd");
		return;
	}

	if (chdir(dir) == -1)
	{
		perror("cd");
		return;
	}

	if (setenv("OLDPWD", old_pwd, 1) == -1)
	{
		perror("cd");
		return;
	}

	if (setenv("PWD", getcwd(NULL, 0), 1) == -1)
	{
		perror("cd");
		return;
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


void setenv_command(char **args)
{
	if (args[1] == NULL || args[2] == NULL)
	{
		perror("setenv");
		return;
	}

	if (setenv(args[1], args[2], 1) == -1)
	{
		perror("setenv");
		return;
	}

}

void unsetenv_command(char **args)
{
	if (args[1] == NULL)
	{
		perror("unsetenv");
		return;
	}

	if (unsetenv(args[1]) == -1)
	{
		perror("unsetenv");
		return;
	}

}
