#include <errno.h>
#include "shell.h"
#define INIT_BUFFER_SIZE 16
#define MAX_INPUT_SIZE 1024

ssize_t _getline(char **lineptr, size_t *n, int fd)
{
	size_t pos = 0;
	ssize_t num_read;
	char *buffer = malloc(MAX_INPUT_SIZE * sizeof(char)), *new_ptr;

	if (!lineptr || !n)
	{
		errno = EINVAL;
		return (-1);
	}

	if (buffer == NULL)
		return (-1);

	if (*lineptr == NULL)
	{
		*lineptr = malloc(INIT_BUFFER_SIZE);
		if (*lineptr == NULL)
			return (-1);
		*n = INIT_BUFFER_SIZE;
	}
	while (1)
	{
		num_read = read(fd, buffer, INIT_BUFFER_SIZE);
		if (num_read == -1)
			return (-1);
		else if (num_read == 0)
			break;
		if (pos + num_read >= MAX_INPUT_SIZE)
			return (-1);
		if (pos + num_read >= *n)
		{
			*n *= 2;
			new_ptr = realloc(*lineptr, *n);

			if (new_ptr == NULL)
				return (-1);
			*lineptr = new_ptr;
		}

		memcpy(*lineptr + pos, buffer, num_read);
		pos += num_read;

		if (buffer[num_read - 1] == '\n')
		{
			(*lineptr)[pos - 1] = '\0';
			return (pos - 1);
		}
	}
	if (pos > 0)
	{
		(*lineptr)[pos] = '\0';
		return (pos);
	}

	free(buffer);
	return (-1);
}

