#include "my_shell.h"

/**
 * sesh_execute - Fork process and replace the child with a new program
 * @arguments: String of tokens
 * @argv: array of arguments
 * @exit_status: exit status
 * Return: Always 1 if successful.
 */

int sesh_execute(char **arguments, char **argv, int *exit_status)
{
	pid_t pid;
	int status; /* for waitpid syscall */
	char *new_arguments;

	/* Check if PATH exists and can be accessed, also tokenize PATH */
	new_arguments = validate_input(arguments, argv);
	if (strcmp(new_arguments, "Fail access") == 0)
	{
		return (1);
	}

	/* Create a forked child process */
	pid = fork();

	if (pid == 0)
	{
		/* Execute another program instead of the child */
		if (execve(new_arguments, arguments, environ) == -1)
		{
			perror("Fail: exec could not launch");
			/*free(new_arguments);*/
			exit(EXIT_FAILURE);
		}
	}

	else if (pid < 0)
	{
		perror("Fork error");
		free(new_arguments);
		return (1);
	}

	else /* in parent process */
	{
		/* Wait for the child process to terminate */
		waitpid(-1, &status, 0);

		/* Check if the child terminated without error */
		if (WIFEXITED(status))
		{
			/* Set the child status to exit_status variable */
			*exit_status = WEXITSTATUS(status);
		}

		/* Evaluate first element of first token */
		if (arguments[0][0] != '/' && arguments[0][0] != '.')
		{
			free(new_arguments);
		}

		return (1);
	}
	return (1);
}

/**
 * sesh_execute_builtins - Choose from an array of builtin functions
 * @args: String of arguments (tokens)
 * @input_stdin: String from input
 * @argv: Array of arguments
 * @exit_status: Exit status
 * Return: Status to stay or exit the main loop, 1 or 0
 */

int sesh_execute_builtins(char **args, char *input_stdin, char **argv, int *exit_status)
{
	int i = 0;

	/* Array of builtin functions of type 'choose_cmd_t' */
	choose_cmd_t options[] = {
		{"exit", sesh_exit},
		{"env", sesh_env},
		{"cd", sesh_cd},
		{"setenv", sesh_setenv},
		{"unsetenv", sesh_unsetenv},
		{NULL, NULL}
	};

	while (options[i].builtin_name)
	{
		/* Check if args[0] matches the built-in function name */
		if (strcmp(options[i].builtin_name, args[0]) == 0)
		{
			/* Call and execute the corresponding builtin function */
			return ((int)((*options[i].builtin_func)(args, input_stdin, exit_status)));
		}
		i++;
	}

	/* If no builtin function is encountered, execute a process */
	return (sesh_execute(args, argv, exit_status));
}
