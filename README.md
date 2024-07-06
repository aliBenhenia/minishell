As beautiful as a shell

Summary
Minishell is a project aimed at creating a simple shell program akin to bash. By working on this project, you will gain practical knowledge about processes and file descriptors in Unix-like systems.

Contents
I. Introduction
II. Common Instructions
III. Mandatory part
IV. Bonus part
V. Submission and peer-evaluation

Chapter I: Introduction
Shells are fundamental in computing history, bridging the gap between human-readable commands and machine execution. Minishell allows you to explore the challenges faced before graphical interfaces became ubiquitous.

Chapter II: Common Instructions
The project must be implemented in C.
Adhere to the Norm, ensuring no undefined behaviors or memory leaks.
Submission includes necessary files like Makefile, headers, and source code.
Comprehensive Makefile rules are required, including $(NAME), all, clean, fclean, and re.
Encouraged to create and use test programs for validation.
Chapter III: Mandatory part
Program Name: minishell
Turn-in files: Makefile, *.h, *.c
Arguments: See detailed list of allowed external functions
Libft authorized: Yes

Description:
Minishell should:

Display a prompt for commands.
Support command history.
Execute commands based on PATH variable or specified paths.
Manage signals with minimal global variables.
Handle quotes and redirections (<, >, <<, >>).
Implement pipes (|) for command chaining.
Expand environment variables and handle special variables like $?.
Manage interactive mode behaviors (ctrl-C, ctrl-D, ctrl-\).
Implement built-in commands: echo, cd, pwd, export, unset, env, exit.
