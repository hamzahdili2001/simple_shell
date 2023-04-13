#include "shell.h"
<<<<<<< HEAD
=======
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> testing
=======
>>>>>>> testing
#include <stdio.h>

char *read_line(void)
{
	char *line = NULL;
	size_t buffer_size = 0;

	if (getline(&line, &buffer_size, stdin) == -1)
	{
			perror("getline");
			exit(EXIT_FAILURE);
	}
	printf("%s", line);
	return (line);
}

void main_loop(void)
{
	char *prompt = "$ ", *line;
	size_t line_length;
	int status = 1;

	do {
		printf("%s", prompt);
		line = read_line();
	} while (status);

}
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> Bahaa
>>>>>>> testing
=======
>>>>>>> Bahaa
>>>>>>> testing

int main (void)
{
	main_loop();
}

