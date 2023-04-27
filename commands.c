#include "shell.h"
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#define PATH_SIZE 4096
/**
 * cd_command - implement cd command
 * @args: arguments
 * Return: Nothing
*/
void cd_command(char **args)
{
	char *dir, *pwd;

	if (args[1] == NULL)
		dir = getenv("HOME");

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
		dir = args[1];

	if (chdir(dir) != 0)
	{
		perror("cd");
		return;
	}
	else
	{
		pwd = getcwd(NULL, 0);
		if (pwd == NULL)
		{
			perror("getcwd");
			return;
		}
		else
		{
			setenv("OLDPWD", getenv("PWD"), 1);
			setenv("PWD", pwd, 1);
			free(pwd);
		}
	}
}

/**
 * env_command - implement env command
 * @args: arguments
 * Return: Nothing.
*/

void env_command(char **args)
{
	char **envptr = environ;

	if (args == NULL)
		return;

	while (*envptr != NULL)
	{
		write(STDOUT_FILENO, *envptr, _strlen(*envptr));
		write(STDOUT_FILENO, "\n", 1);
		envptr++;
	}

}
/**
 * setenv_command - implement setenv command
 * @args: arguments.
 * Return: Nothing
*/

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

/**
 * unsetenv_command - implement unsetenv command
 * @args: arguments
 * Return: Nothing
*/

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
