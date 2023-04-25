#include "shell.h"
#define BUFFER_SIZE 1024
/**
 * _getline - reads a line from a file descriptor
 * @lineptr: pointer to a buffer to store the line
 * @n: pointer to the size of the buffer
 * @fd: file descriptor to read from
 * Return: number of bytes read or -1 on failure
*/
ssize_t _getline(char **lineptr, size_t *n, int fd)
{
	ssize_t num_read;
	size_t position = 0;

	if (!lineptr || !n)
		return (-1);
	if (*lineptr == NULL)
	{
		*lineptr = malloc(BUFFER_SIZE);
		if (*lineptr == NULL)
			return (-1);
		*n = BUFFER_SIZE;
	}
	while (1)
	{
		num_read = read(fd, *lineptr + position, 1);
		if (num_read == -1)
			return (-1);
		else if (num_read == 0)
			break;
		position += num_read;
		if ((*lineptr)[position - 1] == '\n')
			break;
		if (position == *n)
		{
			char *new_ptr = realloc(*lineptr, *n);

			if (new_ptr == NULL)
				return (-1);
			*lineptr = new_ptr;
			*n *= 2;
		}
	}
	if (position == 0)
		return (-1);
	(*lineptr)[position] = '\0';
	return (position);
}
