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
#define DELIM_C ";"	/* Input token delimiter for sesh_tokenizer */

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

/* External variable to access the environment list */
extern char **environ;

/* Main loop */
/**
 * main - Main loop that receives input from the command line
 *		parses it, and executes the corresponding commands
 * @argc: Number of arguments passed to the program
 * @argv: Array of arguments
 * Return: Always 0 on success
 */
int main(int argc __attribute__((unused)),
         char **argv __attribute__((unused)));

/* Tokenizers */
char **sesh_tokenizer(char *input);
char **sesh_tokenizer_path(char *input);
char **validate_semicolon(char *input);

/* Validators */
char *validate_input(char **arguments, char **argv);
int validate_spaces(char *input);

/* Executors */
int sesh_execute(char **arguments, char **argv, int *exit_status);
int sesh_execute_builtins(char **args, char *input_stdin,
                         char **argv, int *exit_status);

/* Built-in functions */
int sesh_cd(char **args, char *input_stdin, int *exit_status);
int sesh_setenv(char **args, char *input_stdin, int *exit_status);
int sesh_unsetenv(char **args, char *input_stdin, int *exit_status);
int sesh_env(char **args, char *input_stdin, int *exit_status);
int sesh_exit(char **args, char *input_stdin, int *exit_status);

/* Helper functions */
void sigintH(int signum);
char *str_concat(char *s1, char *s2);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

#endif
/* MY_SHELL_H */
