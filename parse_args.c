#include "shell.h"

char **parse_args(char *line)
{
	const char *delim = " \t\r\n\a";
	char **token = malloc(sizeof(char *));
	int i =0;

	if (token == NULL)
	{
		perror("malloc error");
		exit(EXIT_FAILURE);
	}
	token[i] = strtok(line, delim);

	while (token[i])
	{
		i++;
		token = realloc(token, sizeof(char *) * (i + 1));
		
		if (token == NULL)
		{
			perror("realloc error");
			exit(EXIT_FAILURE);
		}
		token[i] = strtok(NULL,delim);
	}
	return (token);
}
