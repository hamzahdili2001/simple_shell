#include "shell.h"
#include "echo.h"

/**
 * print_argument - Print an argument to stdout.
 *
 * @arg: The argument to print.
 * @stdout_fd: The file descriptor for stdout.
 */
void print_argument(char arg[], int stdout_fd)
{
	size_t arg_len = strlen(arg);

	write(stdout_fd, arg, arg_len);
}

/**
 * echo_command - Implementation of the shell's `echo` command.
 *
 * @args: The arguments to the `echo` command.
 */
void echo_command(char **args)
{
	int i, no_newline = 0, stdout_fd = 1, last_exit_status = 0;
	char newline = '\n';

	if (args[1] != NULL && _strcmp(args[1], "-n") == 0)
	{
		no_newline = 1;
		args++;
	}
	for (i = 1; args[i] != NULL; i++)
	{
		char *arg = args[i];

		if (_strcmp(arg, "$?") == 0)
		{
			char exit_status_str[16];
			int exit_status_len = 0;

			print_exit_status(exit_status_str, &exit_status_len,
										 last_exit_status, stdout_fd);
		}
		else if (_strcmp(arg, "$$") == 0)
		{
			char pid_str[16];
			int pid_len = 0;

			print_pid(pid_str, &pid_len, stdout_fd);
		}
		else if (arg[0] == '$')
		{
			print_variable(arg);
		}
		else
			print_argument(arg, stdout_fd);

		if (args[i + 1] != NULL)
			write(stdout_fd, " ", 1);
	}

	if (!no_newline)
		write(stdout_fd, &newline, 1);
}



