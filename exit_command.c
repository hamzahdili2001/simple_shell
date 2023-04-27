#include "shell.h"
#include <unistd.h>

/**
 * conv_int - converets str to int
 * @s: string
 * Return: -1 or 0
*/
int conv_int(const char *s)
{
	int sign = 1, digit;
	long int result = 0;

	if (*s == '-')
	{
		sign = -1;
		s++;
	}
	else if (*s == '+')
	{
		s++;
	}

	while (*s != '\0')
	{
		if (*s < '0' || *s > '9')
			return (-1);

		digit = *s - '0';
		result = result * 10 + digit;

		if ((sign == 1 && result > INT_MAX) || (sign == -1 && -result < INT_MIN))
		{
			return (-1);
		}
		s++;
	}
	return (sign * result);
}

/**
 * exit_command - implement exit command
 * @args: arguments
 * Return: Nothing.
*/

void exit_command(char **args)
{
	int exit_status = 0;
	char *message = "Invalid exit status: ";

	if (args[1])
	{
		exit_status = conv_int(args[1]);
		if (exit_status < 0)
		{
			write(STDERR_FILENO, message, _strlen(message));
			write(STDERR_FILENO, args[1], _strlen(args[1]));
			write(1, "\n", 1);
			return;
		}
	}
	exit(exit_status);
}
