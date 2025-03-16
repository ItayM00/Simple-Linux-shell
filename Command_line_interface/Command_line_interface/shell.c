#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "commands.h"
#include "parser.h"
#include "utils.h"

#define BUFFER_SIZE 1024
#define DELIMITER " "
#define PROGRAM_TERMINATOR "exit"


void run_shell();
void excecute_commands(char** args);

char* cwd = NULL;

int main()
{
	run_shell();

	return 0;
}

void run_shell()
{
	fprintf(stdout, "(c) ItayM00 shell. All rights reserved.\n\n");
	cwd = get_cur_directory();

	if (cwd == NULL) {
		fprintf(stderr, "error in retriving the current directory...");
		exit(1);
	}

	// Status to know whether to terminate the shell
	int status = 1;

	do {
		char* args = (char*)malloc(sizeof(char) * BUFFER_SIZE);
		if (args == NULL) {
			fprintf(stderr, "Failed Memory Alocation...\n");
			exit(1);
		}

		print_cur_directory(cwd);

		if (fgets(args, BUFFER_SIZE, stdin) != NULL) {
			args[strcspn(args, "\n")] = '\0';  // Remove newline character with null terminator
			normalize_spaces(&args);

			//If args is empty, continue to the next iteration
			if (args[0] == '\0') {
				free(args);
				continue;
			}

			char** arguments = parse_input_arguments(args);
			excecute_commands(arguments);
		}

		status = strncmp(args, PROGRAM_TERMINATOR, 4);

		free(args);
	} while (status);
}


void excecute_commands(char** args)
{
	if (args == NULL || args[0] == NULL) return;

	if (strcmp(args[0], "echo") == 0) {
		echo(args);
	}
	else if (strcmp(args[0], "cd") == 0) {
		cd(args, &cwd);
	}
	else if (strcmp(args[0], "ipconfig") == 0) {
		ipconfig(args);
	}
	else if (strcmp(args[0], "pwd") == 0) {
		pwd(args, cwd);
	}
	else if (strcmp(args[0], "rmdir") == 0) {
		rmdir_cmd(args, cwd);
	}
	else if (strcmp(args[0], "mkdir") == 0) {
		mkdir_cmd(args, cwd);
	}
	else if (strcmp(args[0], "touch") == 0) {
		touch(args, cwd);
	}
	else if (strcmp(args[0], "rm") == 0) {
		rm(args, cwd);
	}
	else if (strcmp(args[0], "ls") == 0) {
		ls(cwd);
	}
	else if (strcmp(args[0], "clear") == 0) {
		clear(args);
	}
	else if (strcmp(args[0], "help") == 0) {
		help();
	}
	else if (strncmp(args[0], PROGRAM_TERMINATOR, 4) == 0) {
		return;
	}
	else {
		fprintf(stderr, "%s is not recogniseable as a command\n", args[0]);
	}
}