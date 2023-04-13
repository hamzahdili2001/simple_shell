#include "shell.h"
#include <unistd.h>

void main_loop(void)
{
	char *prompt = "($) ", *line;
	size_t line_length;
	int status = 1;

	do {
		write(STDERR_FILENO, &prompt, _strlen(prompt) + 1);
		line = read_line();
	} while (status);
}
