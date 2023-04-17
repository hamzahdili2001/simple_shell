#include "shell.h"

char **parse_line(char *line)
{
	int buffer_size = 64, position = 0;
	char **tokens = malloc(buffer_size * sizeof(char *)), *token;

	if (!tokens)
	{
		write(STDERR_FILENO, "Allocation error\n", _strlen("Allocation error\n"));
		exit(EXIT_FAILURE);
	}

	token = _strtok(line, TOKEN_DELIM);

	while (token != NULL)
	{
		tokens[position] = token;
		position++;

		if (position >= buffer_size)
		{
			buffer_size += 64;
			tokens = realloc(tokens, buffer_size * sizeof(char *));
			if (!tokens)
			{
				write(STDERR_FILENO, "Allocation error\n", _strlen("Allocation error\n"));
				exit(EXIT_FAILURE);
			}
		}

		token = _strtok(NULL, TOKEN_DELIM);
	}
	tokens[position] = NULL;

	return (tokens);
}
