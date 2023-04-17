#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

ssize_t _getline(char **line, size_t *n, FILE *stream)
{
	ssize_t buffer_size = 0, num_chars = 0, byte_read;
	char *buffer = NULL, c;

	if (*line == NULL)
	{
		buffer_size = 128;
		*line = (char *)malloc(buffer_size * sizeof(char));
		if (*line == NULL)
			return (-1);
		*n = buffer_size;
	}

	buffer = *line;

	while (1)
	{
		byte_read = read(fileno(stream), &c, 1);

		if (byte_read == -1)
		{
			return (-1);
		}
		else if (byte_read == 0) {
			buffer[num_chars] = '\0';
			return ((num_chars == 0) ? 0 : num_chars);
		}
		else if (c == '\n')
		{
			buffer[num_chars] = '\0';
			return (num_chars);
		}

		buffer[num_chars] = c;
		num_chars++;


		if (num_chars >= *n)
		{
			buffer_size += 128;
			*line = (char *)realloc(*line, buffer_size * sizeof(char));
			if (*line == NULL)
				return (-1);
		}
	}
}

