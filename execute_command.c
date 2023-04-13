#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void execute_command(char **args)
{
	pid_t pid;
	int status;
	/*ADD CONCAT*/
	char *concat = malloc(_strlen(args[0]) + _strlen("/bin/") + 1);

	/*CHECK MALLOC*/
	if (concat == NULL)
	{
		perror("Allocation faild");
		exit(EXIT_FAILURE);
	}

	/*Concatenate input with "/bin/"*/ 
	strcpy(concat, "/bin/");
	strcat(concat, args[0]);

	pid = fork();
	if (pid == 0)
	{
		if (execve(concat, args, NULL) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	else if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else
	{
		do
		{
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
}
