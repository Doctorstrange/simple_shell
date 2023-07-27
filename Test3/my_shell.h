#ifndef MY_SHELL_H
#define MY_SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

#define BUFSIZE 64      /* Constant buffer size for sesh_tokenizers */
#define DELIM_I " \t\n" /* Input token delimiter for sesh_tokenizer */
#define DELIM_P ":"     /* Path token delimiter for sesh_tokenizer_path */


/* External variable to access the environment list */
extern char **environ;

/* 1. Main loop */
/**
 * main - Main loop that receives input from the command line
 *		parses it, and executes the corresponding commands
 * @argc: Number of arguments passed to the program
 * @argv: Array of arguments
 * Return: Always 0 on success
 */
int main(int argc __attribute__((unused)),
         char **argv __attribute__((unused)));

/* 2. Tokenizers */

char **sesh_tokenizer(char *input);
char **sesh_tokenizer_path(char *input);

/* 3. Validators */
char *validate_input(char **arguments, char **argv);
int validate_spaces(char *input);

/* 4. Executors */
int sesh_execute(char **arguments, char **argv, int *exit_status);
int sesh_execute_builtins(char **args, char *input_stdin,
                         char **argv, int *exit_status);
/**
 * struct choose_cmd - Structure for built-in commands
 * @builtin_name: Name of the built-in command
 * @builtin_func: Pointer to the corresponding built-in function
 */
typedef struct choose_cmd
{
	char *builtin_name;
	int (*builtin_func)(char **, char *, int *);
} choose_cmd_t;


/* 5. Built-in functions */
int sesh_cd(char **args, char *input_stdin, int *exit_status);
int sesh_setenv(char **args, char *input_stdin, int *exit_status);
int sesh_unsetenv(char **args, char *input_stdin, int *exit_status);
int sesh_env(char **args, char *input_stdin, int *exit_status);
int sesh_exit(char **args, char *input_stdin, int *exit_status);

/* 6. Helper functions */
void sigintHandler(int signum);
char *concat_string(char *str1, char *str2);
void *mem_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

#endif
/* MY_SHELL_H */
