#include "shell.h"
#include <unistd.h>


/**
 * _getchar - man getchar
 * Return: EOF
*/
int _getchar(void)
{
	static char buffer[BUFFER_SIZE],  *bufp = buffer;
	static int n;

	if (n == 0)
	{
		n = read(0, buffer, sizeof(buffer));
		bufp = buffer;
	}

	if (--n >= 0)
	{
		return ((unsigned char) *bufp++);
	}
	return (EOF);
}

/**
 * read_line - a pointer function that read the line from user.
 *
 * Return: line.
*/

char *read_line(void)
{
	int position = 0, c, bufsize = BUFFER_SIZE;
	char *buffer = malloc(sizeof(char) * bufsize);

	if (!buffer)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	while (1)
	{
		c = _getchar();
		if (c == EOF || c == '\n')
		{
			buffer[position] = '\0';
			if (c == EOF && position == 0)
			{
				free(buffer);
				return (NULL);
			}
			return (buffer);
		}
		else
		{
			buffer[position] = c;
		}
		position++;
		if (position >= bufsize)
		{
			bufsize += BUFFER_SIZE;
			buffer = realloc(buffer, bufsize);
			if (!buffer)
			{
				perror("malloc");
				exit(EXIT_FAILURE);
			}
		}
	}
	return (buffer);
}
