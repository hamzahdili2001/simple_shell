#include "shell.h"
#include <stdlib.h>

char *read_line(void)
{
	char *line = NULL;
	size_t buffer_size = 0;
	ssize_t bytes_read = getline(&line, &buffer_size, stdin);

	if (bytes_read == -1)
	{
		free(line);
		exit(EXIT_FAILURE);
	}

	if (line[bytes_read - 1] == '\n')
	{
		line[bytes_read - 1] = '\0';
	}

	//remove comments from the input line
	
	char *comment = _strchr(line, '#');
	if (comment != NULL)
	{
		*comment = '\0';
	}
	return (line);
}
