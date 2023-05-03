# Simple Shell
This is a simple Unix shell created as part of the ALX SE curriculum. The shell reads user commands and executes them, similar to the standard Unix shell (/bin/sh).

## Getting Started
To get started with this shell, clone the repository and compile the program using the following command:
`gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh`

This will generate an executable file named hsh. Once compiled, you can run the shell by executing the following command:
`./hsh`

## Usage
This shell supports both interactive and non-interactive modes.

### Interactive Mode 
In interactive mode, the shell displays a prompt (`#cisfun` by default) and waits for user input. The user can enter a command and press `Enter` to execute it.

```
$ ./hsh
$ /bin/ls
hsh main.c shell.c
$ pwd
/home/user/simple_shell
$ exit
$
```

### Non-Interactive Mode 
In non-interactive mode, the shell reads commands from standard input (stdin) and executes them. To use the shell in non-interactive mode, you can pipe a series of commands to it using the following syntax:
```
echo "command1" | ./hsh
```
Alternatively, you can also redirect input from a file:
```
./hsh < commands.txt
```

## The built-ins commands:
`cd [DIRECTORY]`, `exit [status]`, `setenv` and `unsetenv`, `env`, `echo`..
- Handles the `$?` and `$$` variable
- Handles comments `(#)`


## List of allowed functions and system calls
- access (man 2 access)
- chdir (man 2 chdir)
- close (man 2 close)
- closedir (man 3 closedir)
- execve (man 2 execve)
- exit (man 3 exit)
- _exit (man 2 _exit)
- fflush (man 3 fflush)
- fork (man 2 fork)
- free (man 3 free)
- getcwd (man 3 getcwd)
- getline (man 3 getline)
- getpid (man 2 getpid)
- isatty (man 3 isatty)
- kill (man 2 kill)
- malloc (man 3 malloc)
- open (man 2 open)
- opendir (man 3 opendir)
- perror (man 3 perror)
- read (man 2 read)
- readdir (man 3 readdir)
- signal (man 2 signal)
- stat (__xstat) (man 2 stat)
- lstat (__lxstat) (man 2 lstat)
- fstat (__fxstat) (man 2 fstat)
- strtok (man 3 strtok)
- wait (man 2 wait)
- waitpid (man 2 waitpid)
- wait3 (man 2 wait3)
- wait4 (man 2 wait4)
- write (man 2 write)

## Output
This shell produces the exact same output as the standard Unix shell (/bin/sh), including error output. The only difference is that when an error occurs, the name of the program must be equivalent to the `argv[0]`.

## Authors
- Hamza Hdili (@hamzahdili2001)
- BAHAADINE JAOUHARI (@Brexblime)

## Contact
For any questions or issues, please feel free to contact the contributors to this project.
