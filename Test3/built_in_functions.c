include "my_shell.h"

/**
 * sesh_cd - Change directory
 * @args: Array of tokens
 * @input_stdin: Input from stdin
 * @exit_status: Exit status
 * Return: 1 (success)
 */
int sesh_cd(char **args, char *input_stdin, int *exit_status)
{
	/* Check chdir() return value */
	int stat;
	
	/* size of the string current_dir */
	char current_dir[128];

	/* Get the current working directory and save it in current_dir */
	getcwd(current_dir, sizeof(current_dir));

	(void)input_stdin;
	(void)exit_status;

	/* If user inputs "cd" without any other argument */
	if (args[1] == NULL)
		/* Change to home directory */
		stat = chdir(getenv("HOME"));
	/* If user inputs "cd -" */
	else if (strcmp(args[1], "-") == 0)
		/* Change to previous directory */
		stat = chdir(getenv("OLDPWD"));
	/* If user inputs "cd ~" */
	else if (strcmp(args[1], "~") == 0)
		/* Change to home directory */
		stat = chdir(getenv("HOME"));
	/* Change to any path given (absolute or relative) */
	else
		stat = chdir(args[1]);

	/* Check if any chdir() syscall had an error */
	if (stat == -1)
		perror("Error executing cd");

	/* Add the variable OLDPWD to the environment with the value of current_dir */
		/* If OLDPWD already exists, overwrite its value to current_dir */
	setenv("OLDPWD", current_dir, 1);
		/* Update the value of PWD with the current working directory */
	setenv("PWD", getcwd(current_dir, sizeof(current_dir)), 1);
	
	return (1);
}

/**
 * sesh_setenv - Change or add an environment variable
 * @args: Array of tokens from input
 * @input_stdin: Input from stdin
 * @exit_status: Exit status
 * Return: Return 1 if successful, 0 otherwise.
 */
int sesh_setenv(char **args, char *input_stdin, int *exit_status)
{
	int num_tokens = 0; /* Count the number of tokens received */

	(void)input_stdin;
	(void)exit_status;

	/* Get no. of tokens */
	while (args[num_tokens] != NULL)
	{
		num_tokens++;
	}

	/* When we have 3 tokens */
	if (num_tokens == 3)
		/**
		 * args[0] is setenv,
		 * args[1] is the environment,
		 * If args[1] already exists, its value is overwritten to args[2] */
		setenv(args[1], args[2], 1);

	/* Check if the number of tokens is exactly 3 */
	else if (num_tokens != 3)
	{
		fprintf(stderr, "Syntax: \"setenv [KEY] [VALUE]\"\n");
	}
	return (1);
}

/**
 * sesh_unsetenv - Delete an environment variable from the environment
 * @args: Array of tokens from input
 * @input_stdin: Input from stdin
 * @exit_status: Exit status
 * Return: Return 1 if successful, 0 otherwise.
 */
int sesh_unsetenv(char **args, char *input_stdin, int *exit_status)
{
	int num_tokens = 0; /* Count the number of tokens received */

	(void)input_stdin;
	(void)exit_status;

	/* Get no. of tokens */
	while (args[num_tokens] != NULL)
	{
		num_tokens++;
	}

	/* When we have 2 tokens */
	if (num_tokens == 2)
	{
		/* Delete args[1] from the environment */
		unsetenv(args[1]);
	}
	
	/* Check if the number of tokens is exactly 2 */
	else if (num_tokens != 2)
	{
		fprintf(stderr, "Syntax: \"unsetenv [KEY]\"\n");
	}
	return (1);
}

/**
 * sesh_env - Print environment variables
 * @args: Arguments
 * @input_stdin: Input from stdin
 * @exit_status: Exit status
 * Return: Always 1 (success)
 */
int sesh_env(char **args, char *input_stdin, int *exit_status)
{
	int i = 0;

	(void)args;
	(void)input_stdin;
	(void)exit_status;

	/* Check if the built-in environment is empty */
	if (environ[i] == NULL)
	{
		printf("%s", "The built-in env is empty");
		return (1);
	}

	/* Print the environment variables */
	for (i = 0; environ[i]; i++)
	{
		printf("%s\n", environ[i]);
	}
	return (1);
}

/**
 * sesh_exit - Exit built-in function
 * @args: Arguments
 * @input_stdin: Input from stdin
 * @exit_status: Exit status
 * Return: Exit success
 */
int sesh_exit(char **args, char *input_stdin, int *exit_status)
{
	int exit_code = 0;

	(void)args;
	(void)input_stdin;
	(void)exit_status;

	if (args[1] == NULL)
	{
		free(args);
		free(input_stdin);
		exit(*exit_status);
	}

	if (args[2] != NULL)
	{
		fprintf(stderr, "exit: too many arguments\n");
		return (0);
	}

	exit_code = atoi(args[1]);
	free(args);
	free(input_stdin);
	exit(exit_code);
}
