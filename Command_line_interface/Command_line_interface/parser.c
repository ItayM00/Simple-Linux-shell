#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DELIMITER " "

char** parse_input_arguments(char* str)
{
	char** tokens = NULL;
	char* token = NULL;
	int size = 0;

	token = strtok(str, DELIMITER);

	while (token != NULL) {
		tokens = (char**)realloc(tokens, sizeof(char*) * (size + 1));
		if (tokens == NULL) { fprintf(stderr, "Memory Alocation Failed...\n"); exit(1); }
		tokens[size++] = token;

		token = strtok(NULL, DELIMITER);
	}

	// Add null terminator at the end to prevent crashing when excecuting commands
	tokens = (char**)realloc(tokens, sizeof(char*) * (size + 1));
	if (tokens == NULL) { fprintf(stderr, "Memory Allocation Failed...\n"); exit(1); }
	tokens[size] = NULL;

	return tokens;
}

void normalize_spaces(char** str)
{
    int i = 0, j = 0;
    int spaceFound = 0;

    // Trim leading spaces
    while ((*str)[i] == ' ') i++;

    while ((*str)[i] != '\0')
    {
        if ((*str)[i] == ' ')
        {
            if (!spaceFound) {
                (*str)[j++] = ' ';
                spaceFound = 1;
            }
        }
        else {
            (*str)[j++] = (*str)[i];
            spaceFound = 0;
        }
        i++;
    }

    // Trim trailing space
    if (j > 0 && (*str)[j - 1] == ' ') j--;

    (*str)[j] = '\0';
}

void trim_right_by_delimiter(char** str, char delim)
{
    if (*str == NULL) return;

    int size = strlen(*str);
    int i = size - 1;

    while ((*str)[i] != delim && i >= 0)
        i--;

    if (i >= 0) {
        (*str)[i] = '\0';
    }
}