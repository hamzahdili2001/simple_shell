#include "shell.h"

/**
* print_var - helper function for echo_command.
 * @var_name: variable name.
 * Return: Nothing.
*/
void print_var(char *var_name)
{
	int stdout_fd = 1;
	char *var_value;
	size_t var_value_len;

	var_value = getenv(var_name);
	if (var_value != NULL)
	{
		var_value_len = _strlen(var_value);
		write(stdout_fd, var_value, var_value_len);
	}
}


/**
 * print_exit_status - helper function for echo_command.
 * @exit_status_str: exit status strting.
 * @exit_status_len: exit status length.
 * @exit_status: exit status
 * @stdout_fd: file desctiptor.
 * Return: Nothing.
*/

void print_exit_status(char exit_status_str[],
											 int *exit_status_len,
											 int exit_status, int stdout_fd)
{
	char tmp;
	int j;

	if (exit_status == 0)
		exit_status_str[(*exit_status_len)++] = '0';
	else
	{
		while (exit_status != 0)
		{
			exit_status_str[(*exit_status_len)++] = '0' + (exit_status % 10);
			exit_status /= 10;
		}
	}
	for (j = 0; j < *exit_status_len / 2; j++)
	{
		tmp = exit_status_str[j];
		exit_status_str[j] = exit_status_str[*exit_status_len - j - 1];
		exit_status_str[*exit_status_len - j - 1] = tmp;
	}
	write(stdout_fd, exit_status_str, *exit_status_len);
}


/**
 * print_pid - helper function for echo_command.
 * @pid_str: pid string.
 * @pid_len: pid length.
 * @stdout_fd: file desctiptor.
 * Return: Nothing.
*/

void print_pid(char pid_str[], int *pid_len, int stdout_fd)
{
	char tmp;
	int pid = getpid(), j;

	if (pid == 0)
		pid_str[(*pid_len)++] = '0';
	else
	{
		while (pid != 0)
		{
			pid_str[(*pid_len)++] = '0' + (pid % 10);
			pid /= 10;
		}
	}
	for (j = 0; j < *pid_len / 2; j++)
	{
		tmp = pid_str[j];
		pid_str[j] = pid_str[*pid_len - j - 1];
		pid_str[*pid_len - j - 1] = tmp;
	}
	write(stdout_fd, pid_str, *pid_len);
}

/**
 * print_variable - helper function for echo_command.
 * @arg: arguments.
 * Return: Nothing.
*/

void print_variable(char arg[])
{
	print_var(arg + 1);
}



