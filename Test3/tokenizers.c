#include "my_shell.h"


/**
 * sesh_tokenizer - Split the input string into an array of arguments (tokens)
 * @input: String from input (main function)
 * Return: Pointer to the array of tokens
 */
char **sesh_tokenizer(char *input)
{
	int buffer = BUFSIZE, newBuffer = 0, position = 0;
	char **tokens = NULL, *token = NULL;
	char **backup_tokens = NULL;

	/* Allocate memory for the array of tokens */
	tokens = malloc(buffer * sizeof(char *));

	if (tokens == NULL)
	{
		fprintf(stderr, "Memory allocation error\n");
		exit(EXIT_FAILURE);
	}

	/* Tokenize the input string, checking for DELIM_I and replace them with '\0' */
	token = strtok(input, DELIM_I);

	while (token != NULL)
	{
		tokens[position] = token;
		position++;

		/* Reallocate the array of tokens if necessary */
		if (position >= buffer)
		{
			newBuffer = BUFSIZE * 2;
			backup_tokens = tokens;
			tokens = _realloc(tokens, buffer, newBuffer * sizeof(char *));
			if (tokens == NULL)
			{
				free(backup_tokens);
				free(tokens);
				fprintf(stderr, "Memory allocation error\n");
				exit(EXIT_FAILURE);
			}
		}

		/* When memory realloc is done, continue processing the input string */
		token = strtok(NULL, DELIM_I);
	}

	/* Null terminate the array of tokens */
	tokens[position] = NULL;
	return (tokens);
}

/**
 * sesh_tokenizer_path - Split the environment variable PATH into an array of tokens
 * @input: Pointer to environment variable PATH
 * Return: Pointer to the array of tokens
 */
char **sesh_tokenizer_path(char *input)
{
	int buffer = BUFSIZE, newBuffer = 0, position = 0;
	char **tokens = NULL, *token = NULL;
	char **backup_tokens = NULL;

	/* Allocate memory for the array of tokens */
	tokens = malloc(buffer * sizeof(char *));
	if (tokens == NULL)
	{
		fprintf(stderr, "Memory allocation error\n");
		exit(EXIT_FAILURE);
	}

	/* Tokenize PATH string, checking for DELIM_P and replace it with '\0' */
	token = strtok(input, DELIM_P);
	while (token != NULL)
	{
		tokens[position] = token;
		position++;

		/* Reallocate the array of tokens if necessary */
		if (position >= buffer)
		{
			newBuffer = BUFSIZE * 2;
			backup_tokens = tokens;
			tokens = _realloc(tokens, buffer, newBuffer * sizeof(char *));
			if (tokens == NULL)
			{
				free(backup_tokens);
				free(tokens);
				fprintf(stderr, "Memory allocation error\n");
				exit(EXIT_FAILURE);
			}
		}

		/* Once mem realloc is successful, continue processing the PATH string */
		token = strtok(NULL, DELIM_P);
	}

	/* Null terminate the array of tokens */
	tokens[position] = NULL;
	return (tokens);
}


/**
 * validate_semicolon - Split the input string into multiple commands separated by semicolons
 * @input: String from input (main function)
 * Return: Pointer to the array of command strings
 */
char **validate_semicolon(char *input)
{
    int buffer = BUFSIZE, newBuffer = 0, position = 0;
    char **commands = NULL, *command = NULL;
    char **backup_commands = NULL;

    /* Allocate memory for the array of commands */
    commands = malloc(buffer * sizeof(char *));

    if (commands == NULL)
    {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }

    /* Tokenize the input string, checking for DELIM_C and replace them with '\0' */
    command = strtok(input, DELIM_C);

    while (command != NULL)
    {
        commands[position] = command;
        position++;

        /* Reallocate the array of commands if necessary */
        if (position >= buffer)
        {
            newBuffer = BUFSIZE * 2;
            backup_commands = commands;
            commands = _realloc(commands, buffer, newBuffer * sizeof(char *));
            if (commands == NULL)
            {
                free(backup_commands);
                free(commands);
                fprintf(stderr, "Memory allocation error\n");
                exit(EXIT_FAILURE);
            }
        }

        /* Once mem realloc is successful, continue processing the input string */
        command = strtok(NULL, DELIM_C);
    }

    /* Null terminate the array of commands */
    commands[position] = NULL;
    return commands;
}
