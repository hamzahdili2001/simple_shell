#ifndef ECHO_H
#define ECHO_H
void print_var(char *var_name);
void print_exit_status(char exit_status_str[],
											 int *exit_status_len,
											 int exit_status, int stdout_fd);
void print_pid(char pid_str[], int *pid_len, int stdout_fd);
void print_variable(char arg[]);
#endif
