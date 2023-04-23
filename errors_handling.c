#include "shell.h"
/**
 * errors - print error message and return
 * @name: name of the command that caused the error
 * Return: Nothing
*/
void errors(char *name)
{
	perror(name);
}


