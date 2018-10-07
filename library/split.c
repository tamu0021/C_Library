/* Standard header */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/* Self-make header */
/* split header */
#include "../include/split.h"

/* example */
int main()
{
	char **splitedWords = NULL;
	char *string = "abc,de,f,,g";
	char splitWord = ',';
	unsigned short resultSplit = 0;
	unsigned short i = 0;

	splitedWords = (char **)malloc(strlen(string));
	for (i = 0; i < strlen(string); i++)
	{
		splitedWords[i] = (char *)malloc(strlen(string));
	}

	resultSplit = Split(string, splitWord, splitedWords);

	free(splitedWords);
	return SUCCESS;
}

unsigned short Split(char *string, char splitWord, char **splitedWords)
{
	char *stringPart = NULL;
	unsigned short stringPosition = 0;
	unsigned short stringPartPosition = 0;
	unsigned short i = 0;

	/* Max size of stringPart is less than size of string */
	stringPart = (char *)malloc(strlen(string));
	memset(stringPart, '\0', strlen(string));
	if (stringPart == NULL)
	{
		printf("We can't allocate memory.\n");
		return ERROR_CANNOT_ALLOCATE_MEMORY;
	}

	while (stringPosition < strlen(string))
	{
		/* If stringPart is NULL then, we need allocate memory for stringPart. */
		if (stringPart == NULL)
		{
			stringPart = (char *)malloc(strlen(string));
			memset(stringPart, '\0', strlen(string));
		}

		/* Check one word. */
		if (string[stringPosition] == splitWord)
		{
			/* There is the potential for stringPart is NULL. */
			if (stringPart == NULL)
			{
				strcpy(splitedWords[i], "\0");
			}
			else
			{
				strcpy(splitedWords[i], stringPart);
			}

			/* post-processing */
			i++;
			free(stringPart);
			stringPart = NULL;
			stringPartPosition = 0;
			stringPosition++;

			continue;
		}

		/* if (string[position] != splitWord) */
		stringPart[stringPartPosition] = string[stringPosition];

		/* post-processing */
		stringPosition++;
		stringPartPosition++;
	}

	/* Last element */
	if (stringPart == NULL)
	{
		strcpy(splitedWords[i], "\0");
	}
	else
	{
		strcpy(splitedWords[i], stringPart);
	}

	if (stringPart != NULL)
	{
		free(stringPart);
	}

	return SUCCESS;
}