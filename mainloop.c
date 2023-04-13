#include "shell.h"
<<<<<<< HEAD
#include <stdio.h>
#include <stdlib.h>
=======
>>>>>>> Bahaa
#include <unistd.h>

void main_loop(void)
{
<<<<<<< HEAD
	char *prompt = "($) ", *line = malloc(BUFFER_SIZE * sizeof(char *)), **args;
	size_t line_length;
	int status = 1;

	if (line == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	do {
		write(STDERR_FILENO, &prompt, _strlen(prompt));
		line = read_line();
		args = parse_line(line);
		execute_command(args);
		free(line);
		free(args);
	} while (status);
}

=======
	char *prompt = "($) ", *line;
	size_t line_length;
	int status = 1;

	do {
		write(STDERR_FILENO, prompt, _strlen(prompt) + 1);
		line = read_line();
	} while (status);
}
>>>>>>> Bahaa
