#include "shell.h"

/**
 * parse_line - function that parses the line
 * @line: line given
 * Return: Tokens
 */
char **parse_line(char *line)
{
	int buffer_size = BUFFER_SIZE, position = 0;
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
			buffer_size += BUFFER_SIZE;
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
