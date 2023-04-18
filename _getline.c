#include "shell.h"
#include <stdio.h>
#include <stdlib.h>


ssize_t _getline(char **line, size_t *n, FILE *stream)
{
	static char buffer[BUFFER_SIZE], *buffer_pos = buffer;
	ssize_t num_chars = 0, bytes_read;
	char c;

	if (*line == NULL)
	{
		*line = (char *)malloc(BUFFER_SIZE * sizeof(char));
		if (*line == NULL)
			return (-1);

		*n = BUFFER_SIZE;
	}

	while (1)
	{
		if (buffer_pos == buffer)
		{
			bytes_read = read(fileno(stream), buffer, BUFFER_SIZE);
			if (bytes_read == -1)
				return (-1);
			else if (bytes_read == 0) {
				*(*line + num_chars) = '\0';
				return (((num_chars == 0) ? 0 : num_chars));
			}
			buffer_pos = buffer;
		}

		c = *buffer_pos;
		buffer_pos++;
		if (c == '\n')
		{
			*(*line + num_chars) = '\0';
			return (num_chars);
		}
		*(*line + num_chars) = c;
		num_chars++;

		if (num_chars >= *n)
		{
			*n += BUFFER_SIZE;
			*line = (char *)realloc(*line, *n * sizeof(char));
			if (*line == NULL)
				return (-1);
		}
	}
}

