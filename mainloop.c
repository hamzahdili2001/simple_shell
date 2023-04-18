#include "shell.h"
#include <stdio.h>
#include <unistd.h>

void main_loop(void)
{
	char *prompt = "($) ", *line, **args;
	ssize_t num_bytes;
	int status = 1;


	do {
		write(STDERR_FILENO, prompt, _strlen(prompt));
	  /*read input from a pipe if available, otherwise read from stdin*/
		if (isatty(STDERR_FILENO) == 0)
		{
			line = read_line();
		}
		else {
			line = malloc(BUFFER_SIZE * sizeof(char));
			if (line == NULL)
			{
				perror("malloc");
				exit(EXIT_FAILURE);
			}
			num_bytes = read(STDIN_FILENO, line, BUFFER_SIZE);
			if (num_bytes < 0)
			{
				perror("read");
				free(line);
				exit(EXIT_FAILURE);
			}

			if (num_bytes == 0)
			{
				free(line);
				break;
			}
			line[num_bytes] = '\0';
		}
		
		args = parse_line(line);

		if (args[0] != NULL && _strcmp(args[0], "exit") == 0)
		{
			free(line);
			free(args);
			status = 0;
			break;
		}
		execute_command(args);
		free(line);
		free(args);
	} while (status);
}

