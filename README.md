# Simple-Linux-shell
A simple linux like shell made with C

## Overview
This is a custom shell implemented in C. It provides basic command execution without using forks or background tasks. The shell includes custom implementations of specific commands.

## Features
- Executes commands without creating child processes
- Clear screen functionality
- User-friendly prompt


## Available Commands
- **echo [text]** - Print text to the terminal
- **cd [dir or path]** - Change the current directory
- **ipconfig** - Display network configuration
- **pwd** - Print the current directory
- **rmdir [dir]** - Remove a directory
- **mkdir [dir]** - Create a new directory
- **rm [file]** - Delete a file
- **touch [file]** - Create a new file
- **clear** - Clear the screen
- **exit** - Exit the shell
- **help** - Show this help message

## Usage
Simply enter a command followed by any necessary arguments and press **Enter**. The shell will process the input and execute the corresponding action.

## Notes
- This shell is a lightweight implementation and may not support all features of a standard Linux shell.
- Ensure you enter valid paths and filenames to prevent errors.


## Future Improvements
- Adding more built-in commands
- Implementing child process and piping
- Improving error handling
