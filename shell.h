#ifndef SHELL_H
#define SHELL_H
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <ncurses.h>
#define TOKEN_DELIM " \t\r\n\a;"
#define BUFFER_SIZE 1024
#define NUM_USER_COMMANDS 6
extern int last_exit_status;
void main_loop(void);
int _strlen(char *str);
int _strcmp(const char *s1, const char *s2);
char *read_line(void);
void execute_command(char **args);
char **parse_line(char *line);
char *_strcat(char *dest, char *src);
char *_strcpy(char *dest, char *src);
void env_command(char **args);
void exit_command(char **args);
void cd_command(char **args);
void setenv_command(char **args);
void unsetenv_command(char **args);
void clear_command(char **args);
char *_strtok(char* str, const char* delim);
char *_strchr(const char* str, int c);
void echo_command(char **args);
typedef struct 
{
	char *command_name;
	void (*command_function)(char **args);
} user_command_t;

#endif
