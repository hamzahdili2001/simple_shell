#include "shell.h"

char *read_line(void)
{
	char *line = NULL;
	size_t buffer_size = 0;

	if (getline(&line, &buffer_size, stdin) == -1)
	{
		perror("getline");
		exit(EXIT_FAILURE);
	}
	return (line);
}
