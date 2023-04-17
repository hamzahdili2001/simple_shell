#include "shell.h"
#include <stdio.h>
#include <unistd.h>

void main_loop(void)
{
	char *prompt = "($) ", *line = malloc(BUFFER_SIZE * sizeof(char *)), **args;
	size_t line_length;
	int status = 1;

	if (line == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	do {
		write(STDERR_FILENO, prompt, _strlen(prompt));

	  /*read input from a pipe if available, otherwise read from stdin*/
		if (isatty(STDERR_FILENO) == 0)
		{
			line = fgets(line, BUFFER_SIZE, stdin);
			if (line == NULL)
			{
				break;
			}
		}
		else {
			line = read_line();
		}
		
		args = parse_line(line);

		if (args[0] != NULL && strcmp(args[0], "exit") == 0)
		{
			free(line);
			free(args);
			exit(EXIT_SUCCESS);
		}
		execute_command(args);
		free(line);
		free(args);
	} while (status);
}

