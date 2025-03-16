#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <io.h>
#include "utils.h"
#include "parser.h"

#define BUFFER_SIZE 1024
#define INVALID_CHARS "/\\:*?\"<>|"

void echo(char** args)
{
	if (args[1] != NULL)
		print_str_arr(args + 1);
	else
		fprintf(stdout, "\"\"\n");
}

void cd(char** args, char** cwd)
{
	if (args[1] != NULL) {

		if (strcmp(args[1], ".") == 0) {
			return; // Do nothing, as "." represents the current directory
		}

		if (strcmp(args[1], "..") == 0) {
			trim_right_by_delimiter(cwd, '\\'); // Remove last directory
			return;
		}

		int isDirFound = is_directory_exists(args[1]);

		if (isDirFound) {
			free(*cwd);
			*cwd = _strdup(args[1]);
			fprintf(stdout, "\n");
		}
		else if (isDirFound == 0) {
			fprintf(stderr, "cd: directory not found\n");
		}
	}
	else {
		fprintf(stderr, "cd: missing directory argument\n");
	}
}

void ipconfig(char** args)
{
	if (args[1] != NULL)
		fprintf(stderr, "ipconfig: too many arguments entered\n");
	else {
		system("ipconfig");
	}
}

void pwd(char** args, char* cwd)
{
	if (args[1] == NULL)
		fprintf(stdout, "%s\n\n", cwd);
	else
		fprintf(stderr, "pwd: too many arguments entered\n");
}

void rmdir_cmd(char** args, char* cwd)
{
	int isDirDeleted = -1;
	char* del_dir = (char*)malloc(sizeof(char) * BUFFER_SIZE);
	if (args[1] != NULL) {
		if (strstr(args[1], "\\") == NULL) {
			snprintf(del_dir, BUFFER_SIZE, "%s\\%s", cwd, args[1]);
		}
		else {
			strncpy(del_dir, args[1], BUFFER_SIZE - 1);
			del_dir[BUFFER_SIZE - 1] = '\0';
		}

		isDirDeleted = _rmdir(del_dir);
		if (isDirDeleted == 0) {
			fprintf(stdout, "removed directory %s\n", args[1]);
		}
		else {
			fprintf(stderr, "rmdir: directory not found\n");
		}
	}
	else {
		fprintf(stderr, "rmdir: missing directory argument\n");
	}
	free(del_dir);
}

void mkdir_cmd(char** args, char* cwd)
{
	int isDirMade = -1;
	char* new_dir = (char*)malloc(sizeof(char) * BUFFER_SIZE);
	if (args[1] != NULL) {
		if (strstr(args[1], "\\") == NULL) {
			snprintf(new_dir, BUFFER_SIZE, "%s\\%s", cwd, args[1]);
		}
		else {
			strncpy(new_dir, args[1], BUFFER_SIZE - 1);
			new_dir[BUFFER_SIZE - 1] = '\0';
		}

		isDirMade = _mkdir(new_dir);

		if (isDirMade == 0) {
			fprintf(stdout, "created directory %s\n", args[1]);
		}
		else {
			fprintf(stderr, "mkdir: directory already exists or could not be created\n");
		}
	}
	else {
		fprintf(stderr, "mkdir: missing directory argument\n");
	}
	free(new_dir);
}

void ls(char** args)
{

}

void touch(char** args, char* cwd) {
    if (args[1] == NULL) {
        fprintf(stderr, "touch: missing file name\n");
        return;
    }

    // Extract just the filename from the path
    char* filename = args[1];
    char* last_slash = strrchr(args[1], '/');
    char* last_backslash = strrchr(args[1], '\\');

    if (last_slash != NULL || last_backslash != NULL) {
        if (last_slash > last_backslash) {
            filename = last_slash + 1;
        }
        else if (last_backslash != NULL) {
            filename = last_backslash + 1;
        }
    }

    // check if the filename part is valid (not the whole path)
    if (!is_valid_filename(filename)) {
        fprintf(stderr, "Error: Invalid file name '%s'.\n", filename);
        fprintf(stderr, "File names cannot contain: %s\n", INVALID_CHARS);
        return;
    }

    // Use the path directly if it contains / or \, otherwise combine with cwd
    char* path = NULL;
    if (strchr(args[1], '/') != NULL || strchr(args[1], '\\') != NULL) {
        // It's already a path
        path = _strdup(args[1]);
    }
    else {
        // just a filename, append to current working directory
        path = concetrate_strings(cwd, "/");
        char* full_path = concetrate_strings(path, args[1]);
        free(path);
        path = full_path;
    }

    if (path == NULL) {
        fprintf(stderr, "Memory Allocation Error\n");
        return;
    }

    // Create the file
    FILE* file = fopen(path, "w");
    if (file == NULL) {
        fprintf(stderr, "Error creating file: %s\n", path);
        free(path);
        return;
    }

    fprintf(stdout, "File '%s' created successfully!\n", path);
    fclose(file);
    free(path);
}

void rm(char** args, char* cwd) {
    if (args[1] == NULL) {
        fprintf(stderr, "rm: missing file name\n");
        return;
    }

    // Extract just the filename from the path
    char* filename = args[1];
    char* last_slash = strrchr(args[1], '/');
    char* last_backslash = strrchr(args[1], '\\');

    if (last_slash != NULL || last_backslash != NULL) {
        if (last_slash > last_backslash) {
            filename = last_slash + 1;
        }
        else if (last_backslash != NULL) {
            filename = last_backslash + 1;
        }
    }

    // Now check if the filename part is valid (not the whole path)
    if (!is_valid_filename(filename)) {
        fprintf(stderr, "Error: Invalid file name '%s'.\n", filename);
        fprintf(stderr, "File names cannot contain: %s\n", INVALID_CHARS);
        return;
    }

    // Use the path directly if it contains / or \, otherwise combine with cwd
    char* path = NULL;
    if (strchr(args[1], '/') != NULL || strchr(args[1], '\\') != NULL) {
        // already a path
        path = _strdup(args[1]);
    }
    else {
        // just a filename, append to current working directory
        path = concetrate_strings(cwd, "/");
        char* full_path = concetrate_strings(path, args[1]);
        free(path);
        path = full_path;
    }

    if (path == NULL) {
        fprintf(stderr, "Memory Allocation Error\n");
        return;
    }

    // Remove the file
    if (remove(path) == 0) {
        fprintf(stdout, "File deleted successfully.\n");
    }
    else {
        fprintf(stderr, "Error: Unable to delete the file.\n");
    }
    free(path);
}

void clear(char** args)
{
	if (args[1] != NULL)
		fprintf(stderr, "clear: too many arguments entered\n");
	else {
		system("cls");
	}
}

void help()
{
	puts("\n\tHello there! This is a simple (Linux-like) shell I built.\n"
		"You're welcome to use it as long as you're careful, because this isn't a pro product.\n");

	fprintf(stdout, "\nAvailable Commands:\n");
	fprintf(stdout, "-------------------\n");
	fprintf(stdout, "echo [text]        - Print text to the terminal\n");
	fprintf(stdout, "cd [dir or path]   - Change the current directory\n");
	fprintf(stdout, "ipconfig          - Display network configuration\n");
	fprintf(stdout, "pwd               - Print the current directory\n");
	fprintf(stdout, "rmdir [dir]       - Remove a directory\n");
	fprintf(stdout, "mkdir [dir]       - Create a new directory\n");
	fprintf(stdout, "ls                - List files in the current directory\n");
	fprintf(stdout, "rm [file]	- Delete a file\n");
	fprintf(stdout, "touch [file]	- Create a file\n");
	fprintf(stdout, "clear             - Clear the screen\n");
	fprintf(stdout, "exit              - Exit the shell\n");
	fprintf(stdout, "help              - Show this help message\n\n");
}
