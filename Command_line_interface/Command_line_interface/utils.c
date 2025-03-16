#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024
#define INVALID_CHARS "/\\:*?\"<>|"

char* get_cur_directory()
{
	// Allocation variable for the curent directory
	char* local_cwd = (char*)malloc(sizeof(char) * BUFFER_SIZE);
	if (local_cwd == NULL) {
		fprintf(stderr, "Failed Memory Alocation...\n");
		exit(1);
	}

	// Retrives the current directory
	if (_getcwd(local_cwd, BUFFER_SIZE) != NULL) {
		return local_cwd;
	}
	else {
		fprintf(stderr, "Error retrieving current directory.\n");
		return NULL;
	}
}

void print_cur_directory(char* cwd)
{
	fprintf(stdout, "\n%s>", cwd);
}

void print_str_arr(char** arr)
{
	int i, quote_status;

	quote_status = (*(arr[0]) == '"') ? 1 : 0;

	if (!quote_status) fprintf(stdout, "\"");

	for (i = 0; arr[i] != NULL; i++) {
		if (arr[i + 1] == NULL)
			fprintf(stdout, "%s", arr[i]);
		else
			fprintf(stdout, "%s ", arr[i]);
	}

	if (!quote_status)
		fprintf(stdout, "\"\n");
	else
		fprintf(stdout, "\n");
}

int is_directory_exists(char* path)
{
	int isDirFound = _access(path, 0); // returns 0 if found else returns -1

	return (isDirFound == 0) ? 1 : 0;
}

char* concetrate_strings(const char* s1, const char* s2) 
{
	if (s1 == NULL || s2 == NULL) {
		fprintf(stderr, "Error: NULL string provided.\n");
		return NULL;
	}

	int size1 = strlen(s1);
	int size2 = strlen(s2);

	char* newS = (char*)malloc(sizeof(char) * (size1 + size2 + 1));
	if (newS == NULL) { fprintf(stderr, "Memory Allocation Error\n"); return NULL;}

	strcpy(newS, s1);
	strcat(newS, s2);

	return newS;
}

int is_valid_filename(const char* filename) 
{
	if (filename == NULL || strlen(filename) == 0) {
		return 0; // Empty or NULL filename
	}

	if (strpbrk(filename, INVALID_CHARS) != NULL) {
		return 0; // Contains forbidden characters
	}

	return 1; // Valid filename
}