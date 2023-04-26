#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#define PATH_SIZE 4096
/**
 * cd_command - implement cd command
 * @args: arguments
 * Return: Nothing
*/
void cd_command(char **args)
{
	char *dir, old_pwd[PATH_SIZE], *current_dir;

	if (args[1] == NULL)
		dir = getenv("HOME");
	else if (_strcmp(args[1], "-") == 0)
		dir = getenv("OLDPWD");
	else
		dir = args[1];

	if (dir == NULL)
		errors("cd");

	if (getcwd(old_pwd, PATH_SIZE) == NULL)
		errors("cd");

	if (chdir(dir) == -1)
		errors("cd");

	current_dir = getcwd(NULL, 0);

	if (current_dir == NULL)
		errors("cd");

	if (setenv("PWD", current_dir, 1) == -1)
		errors("cd");
}

/**
 * exit_command - implement exit command
 * @args: arguments
 * Return: Nothing.
*/

void exit_command(char **args)
{
	int status = 0, sign = 1;
	const char *str = args[1];

	if (args[1] != NULL)
	{
		if (*str == '-')
		{
			sign = -1;
			str++;
		}
		while (*str != '\0')
		{
			if (!_isdigit(*str))
			{
				perror("exit");
				exit(EXIT_FAILURE);
			}
			status = status * 10 + (*str - '0');
			str++;
		}
		status *= sign;
	}
	exit(status);
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
