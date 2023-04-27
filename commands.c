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
		perror("cd");
	else
	{
		pwd = getcwd(NULL, 0);
		if (pwd == NULL)
			perror("getcwd");
		else
		{
			setenv("OLDPWD", getenv("PWD"), 1);
			setenv("PWD", pwd, 1);
			free(pwd);
		}
	}
}

/**
 * exit_command - implement exit command
 * @args: arguments
 * Return: Nothing.
*/

void exit_command(char **args)
{
	int status, i, is_digit, str_len, big_number;
	unsigned int ustatus;

	if (args[1] != NULL)
	{
		ustatus = _atoi(args[1]);
		is_digit = 1;
		str_len = 0;
		big_number = ustatus > (unsigned int)INT_MAX;

		for (i = 0; args[1][i] != '\0'; i++)
		{
			if (!_isdigit(args[1][i]))
			{
				is_digit = 0;
				break;
			}
			str_len++;
		}
		if (!is_digit || str_len > 10 || big_number)
		{
			perror("exit");
			exit(2);
		}
		status = (int)ustatus;
		exit(status);
	}
	else
	{
		exit(0);
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
