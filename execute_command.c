#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

void execute_command(char **args)
{
	pid_t pid;
	int status;
	char *command;
	
	if (args[0] == NULL)
	{
		return;
	}
	if (strcmp(args[0], "exit") == 0)
	{
		exit(EXIT_SUCCESS);
	}
	if (strcmp(args[0], "env") == 0)
	{
		execute_env();
		return;
	}
	if (args[0][0] == '/')
	{
		command = args[0];
	}
	else
	{
		command = malloc(_strlen(args[0]) + _strlen("/bin/") + 1);
		if (command == NULL)
		{
			perror("Allocation faild");
			exit(EXIT_FAILURE);
		}
		_strcpy(command, "/bin/");
		_strcat(command, args[0]);
	}

	pid = fork();
	if (pid == 0)
	{
		if (execve(command, args, NULL) == -1)
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

	/*Free command*/
	if (command != args[0])
		free(command);
}
