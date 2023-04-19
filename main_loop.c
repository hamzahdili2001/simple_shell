#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * main_loop - function where everyting starts
 *
 * Return: Nothing.
*/

void main_loop(void)
{
	char *prompt = "($) ", *line = malloc(BUFFER_SIZE * sizeof(char *)), **args;
	size_t line_length;
	int status = 1, exit_status;

	if (line == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	do {
		write(STDERR_FILENO, prompt, _strlen(prompt));
		if (isatty(STDERR_FILENO) == 0)
		{
			line = read_line();
			if (line == NULL)
			{
				break;
			}
		}
		else
		{
			line = read_line();
		}
		args = parse_line(line);
		if (args[0] != NULL && _strcmp(args[0], "exit") == 0)
		{
			exit_status = EXIT_SUCCESS;
			if (args[1] != NULL)
			{
				exit_status = atoi(args[1]);
			}
			free(line);
			free(args);
			exit(exit_status);
		}
		execute_command(args);
		free(line);
		free(args);
	} while (status);
}

