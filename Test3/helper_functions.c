#include "my_shell.h"

/**
 * sigintHandler - Handles SIGINT (CTRL + C) signal
 * @signum: Signal number caught by the signal, 2 for SIGINT
 * Return: void
 */

void sigintHandler(int signum)
{
	if (signum == SIGINT)
	{
		write(2, "\n\n#(ಠ_ಠ)->$  ", 17);
	}
}


/**
 * concat_string - Concatenates two strings
 * @str1: 1st string
 * @str2: 2nd string
 * Return: Pointer to the concatenated string
 */
char *concat_string(char *str1, char *str2)
{
	char *result;
	unsigned int len1, len2, i, j;

	if (str1 == NULL)
	{
		str1 = "";
	}
	if (str2 == NULL)
	{
		str2 = "";
	}

	for (len1 = 0; str1[len1] != '\0'; len1++)
		continue;

	for (len2 = 0; str2[len2] != '\0'; len2++)
		continue;

	len2++;

	result = malloc((len1 + len2) * sizeof(char));

	if (result == NULL)
		return (0);

	for (i = 0; i < (len1 + len2); i++)
	{
		if (i < len1)
			result[i] = str1[i];
		else
			result[i] = str2[i - len1];
	}
	return (result);
}

/**
 * mem_realloc - Reallocate a memory block
 * @ptr: Pointer to array
 * @old_size: Old size
 * @new_size: New size
 * Return: A pointer to the allocated memory
 */

 void *mem_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
    char *newPtr;
    char *oldPtr;
    unsigned int i;

    if (ptr == NULL)
        return malloc(new_size);

    if (new_size == 0 && ptr != NULL)
    {
        free(ptr);
        return NULL;
    }

    if (new_size == old_size)
        return ptr;

    oldPtr = (char *)ptr;

    newPtr = malloc(new_size * sizeof(char));
    if (newPtr == NULL)
    {
        free(newPtr);
        return NULL;
    }

    if (new_size > old_size)
    {
        for (i = 0; i < old_size; i++)
            newPtr[i] = oldPtr[i];
    }
    else if (new_size < old_size)
    {
        for (i = 0; i < new_size; i++)
            newPtr[i] = oldPtr[i];
    }
    free(oldPtr);
    return newPtr;
}
