#include "shell.h"
#include <stdlib.h>
/**
 * main_errors_helper - error handler to prevent more than 40 line
 * @text: error message
 * @code: exit code
 * Return: Nothing.
*/
void main_errors_helper(char *text, int code)
{
	perror(text);
	exit(code);
}

/**
 * main - the program starts here.
 *
 * Return: 0
*/
int main(void)
{
	char *prompt = "($) ", *line = malloc(BUFFER_SIZE * sizeof(char *)), **args;
	size_t line_length;
	int status = 1, exit_status;

	if (line == NULL)
		main_errors_helper("malloc", EXIT_FAILURE);
	do {
		write(STDERR_FILENO, prompt, _strlen(prompt));
		if (isatty(STDERR_FILENO) == 0)
		{
			line_length = read(STDIN_FILENO, line, BUFFER_SIZE);
			if (line_length == -1)
				main_errors_helper("read", EXIT_FAILURE);
			if (line_length == 0)
				break;
		}
		else
			line = read_line();

		args = parse_line(line);
		if (args[0] != NULL)
		{
			if (_strcmp(args[0], "exit") == 0)
			{
				exit_status = EXIT_SUCCESS;
				if (args[1] != NULL)
					exit_status = atoi(args[1]);
				free(line);
				free(args);
				exit(exit_status);
			}
			execute_command(args);
			free(args);
		}
		free(line);
	} while (status);
	return (0);
}
