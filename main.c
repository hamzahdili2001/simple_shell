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
	char *prompt = "#cisfun$ ", *line, **args;
	int status = 1, exit_status;

	do {
		if (isatty(STDERR_FILENO))
		{
			write(STDERR_FILENO, prompt, _strlen(prompt));
		}

		line = read_line();
		if (line == NULL)
		{
			free(line);
			return (0);
		}

		args = parse_line(line);
		if (args[0] != NULL)
		{
			if (_strcmp(args[0], "exit") == 0)
			{
				exit_status = EXIT_SUCCESS;
				if (args[1] != NULL)
					exit_status = _atoi(args[1]);
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
