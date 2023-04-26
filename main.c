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
 * @argc: argument length
 * @argv: arguments
 * Return: 0
*/
int main(int argc, char *argv[])
{
	char *prompt = "#cisfun$ ", *line, **args;
	int status = 1;

	(void)argc;

	do {
		if (isatty(STDERR_FILENO))
		{
			write(STDERR_FILENO, prompt, _strlen(prompt));
		}

		line = read_line();
		if (line == NULL)
		{
			free(line);
			break;
		}

		args = parse_line(line);
		if (args[0] != NULL)
		{
			execute_command(args, argv);
			free(args);
		}
		free(line);
	} while (status);
	return (0);
}
