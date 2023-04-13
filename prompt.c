#include "shell.h"

/**
 * main - entry point
 * @ac: number of command line arguments
 * @argv: array of command line argument strings
 * Return: 0 on success, non-zero on failure
*/
int main(int ac, char **argv)
{
	char *prompt = "($)";
	char *lineptr = NULL;
	size_t n = 0;

	/* unused variables */
	(void) ac;
	(void) argv;

	while (1)
	{
		printf("%s", prompt);
		if (getline(&lineptr, &n, stdin) == -1)
		{
			perror("getline");
			exit(EXIT_FAILURE);
		}
		printf("%s\n", lineptr);

		free(lineptr);
	}
	return (0);
}
