#include "shell.h"
#include <stdlib.h>

user_command_t user_commands[] = {
	{"cd", cd_command},
	{"env", env_command},
	{"exit", exit_command},
	{"clear", clear_command},
};

void execute_command(char **args)
{
	pid_t pid;
	int status, i;
	user_command_t *cmd;
	char *bn_command;
	
	if (args[0] == NULL)
	{
		return;
	}
	/*Search for the command in the commands array*/
	for (i = 0; i < NUM_USER_COMMANDS; i++)
	{
		if (strcmp(args[0], user_commands[i].command_name) == 0)
		{
			cmd = &user_commands[i];
			cmd->command_function(args);
			return;
		}
	}
	if (args[0][0] == '/')
	{
		cmd = NULL;
	}
	else
	{
		bn_command = malloc(_strlen(args[0]) + _strlen("/bin/") + 1);
		if (bn_command == NULL)
		{
			perror("Allocation faild");
			exit(EXIT_FAILURE);
		}
		_strcpy(bn_command, "/bin/");
		_strcat(bn_command, args[0]);
		cmd = malloc(sizeof(user_commands));
		cmd->command_name = bn_command;
		cmd->command_function = NULL;
	}

	pid = fork();
	if (pid == 0)
	{
		if (execve(bn_command, args, NULL) == -1)
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
	if (bn_command != args[0])
		free(bn_command);
}
