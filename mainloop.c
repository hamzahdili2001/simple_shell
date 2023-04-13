#include "shell.h"
#include <unistd.h>

void main_loop(void)
{
	char *prompt = "($) ", *line;
	size_t line_length;
	int status = 1;
	char **environ;
	do {
		write(STDERR_FILENO, prompt, _strlen(prompt) + 1);
		line = read_line();
		char **args = parse_args(line);
		pid_t pid = fork();

		if (pid == -1)
		{
			perror("fork");
		}
		else if (pid == 0)
		{
			if (execve(args[0], args, environ) == -1)
			{
				perror("execve");
				exit(EXIT_FAILURE);
			}
			exit(EXIT_SUCCESS);
		}
		else
		{
			wait(NULL);
		}
		free(line);
		free(args);
	} while (status);
}
