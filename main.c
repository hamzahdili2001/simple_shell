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
	int status = 1;

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
			execute_command(args);
			free(args);
		}
		free(line);
	} while (status);
	return (0);
}
