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
 * sesh_tokenizer - Split the input string into an array of arguments (tokens)
 * @input: String from input (main function)
 * Return: Pointer to the array of tokens
 */
char **sesh_tokenizerzero(char *input, int *c)
{
	int buffer = BUFSIZE2, newBuffer = 0, position = 0;
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
	token = strtok(input, DELIM_C);

	while (token != NULL)
	{
		tokens[position] = token;
		position++;
			printf("the value of c is now: %d\n", *c);

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
		token = strtok(NULL, DELIM_C);
			(*c)++;
	}

	/* Null terminate the array of tokens */
	tokens[position] = NULL;
	(*c)--;
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
