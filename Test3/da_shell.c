#include "my_shell.h"

/**
 * main - Main loop, receive input from CLI, parse, and execute it
 * @argc: Number of arguments passed to the program
 * @argv: Array of arguments
 * Return: (0) when successful
 */

int main(int argc __attribute__((unused)), char **argv __attribute__((unused)))
{
	char **arguments = NULL; /* Array of tokens obtained from sesh_tokenizer */
	char *input_stdin = NULL; /* Input string from stdin */
	int status_return = 1;
	int exit_status = 0;
	size_t size = 0; /* Size of input_stdin for getline */
	ssize_t n = 0; /* To check getline return value and EOF */

	/* Register the SIGINT signal handler */
	/* signal(SIGINT, sigintHandler); */

	/* Check loop status */
	while (status_return && n != EOF)
	{
		/* Set size to 0 for every new input */
		size = 0;

		/* Return 1 if the file in the argument refers to the terminal */
		status_return = isatty(STDIN_FILENO);
		if (status_return)
		{
			/* print prompt to stdout */
			write(STDOUT_FILENO, "#cisfun$ ", 10);
		}


		/* Register the SIGINT signal handler */
		signal(SIGINT, sigintHandler);


		/* Store the input_stdin string and check for EOF or any error */
		n = getline(&input_stdin, &size, stdin);

			/* If EOF or any other error is encountered */
		if (n == -1)
		{
			free(input_stdin);
			break;
		}

			/* Validate spaces, tabs, and line breaks */
		if (validate_spaces(input_stdin))
		{
			free(input_stdin);
			continue;
		}

			/* Split the input_stdin string into tokens */
		arguments = sesh_tokenizer(input_stdin);
			/* If an empty character is encountered, skip to the next character */
		if (*arguments[0] == '\0')
		{
			free(input_stdin);
			free(arguments);
			continue;
		}

		/* Pass the array of tokens to choose from builtin functions */
		status_return = sesh_execute_builtins(arguments, input_stdin, argv, &exit_status);

		/* Free memory for input_stdin after executing builtins */
		free(input_stdin);

		/* Free memory for arguments */
		free(arguments);
		
	}

	return (0);
}
