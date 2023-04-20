#include "shell.h"
#include <unistd.h>

/**
 * read_line - a pointer function that read the line from user.
 *
 * Return: line.
*/


char *read_line(void)
{
	char *line = NULL, *comment;
	size_t buffer_size = 0;
	ssize_t bytes_read = _getline(&line, &buffer_size, STDIN_FILENO);

	if (bytes_read == -1)
	{
		free(line);
		exit(EXIT_FAILURE);
	}

	if (line[bytes_read - 1] == '\n')
	{
		line[bytes_read - 1] = '\0';
	}

	/*remove comments from the input line*/
	comment = _strchr(line, '#');
	if (comment != NULL)
	{
		*comment = '\0';
	}
	return (line);
}
