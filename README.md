                                       SIMPLE_SHELL
The Simple Shell Project was successfully executed using the C programming language with the assistance of the Shell Betty linter.

General Project Requirements:

The code was compiled on an Ubuntu 20.04 LTS system employing the GCC compiler, with the compiler options -Wall, -Werror, -Wextra, -pedantic, and -std=gnu89.
All source code files were structured to end with a newline character.
A mandatory README.md file was included at the root of the project folder.
The Betty style guidelines were adhered to and verified using betty-style.pl and betty-doc.pl.
The shell was meticulously crafted to prevent memory leaks.
Each source code file was limited to no more than five functions.
All header files were protected with include guards.
Project Description:

The 'hsh' is a minimalist UNIX command language interpreter designed to read and execute commands from both files and standard input.

Functionality of 'hsh':

'hsh' presents a prompt and awaits user input.
It spawns a child process to evaluate the entered command.
The shell checks for built-in commands, aliases in the PATH, and local executable programs.
The child process executes the command, accepting any associated arguments.
After command execution, the program returns to the parent process and displays the prompt, ready for the next command.
The program can be exited by pressing Ctrl-D or entering "exit" (with or without a status).
This shell also functions effectively in non-interactive mode.
Compilation Command:

To compile the 'hsh' shell, use the following command:

gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
