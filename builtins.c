#include "main.h"

/**
* handle_builtin_command - This command handles builtin commands
* @tokens: tokenisation.
* Return: zero.
*/
int handle_builtin_command(char *tokens[])
{
	if (tokens[0] == NULL)
	{
	return (1);
	}
	else if (strcmp(tokens[0], "cd") == 0)
	{
	/* Handle the "cd" command to change directories */
	if (tokens[1] != NULL)
	{
		if (chdir(tokens[1]) != 0)
			perror("chdir");
	}
	else
	{
	const char *error_message = "cd: missing argument\n";
		write(STDERR_FILENO, error_message, strlen(error_message));
	}
	return (1); /* Command handled */
	}
	else if (strcmp(tokens[0], "exit") == 0)
	{
	/* Handle the "exit" command to exit the shell */
	exit(0);
	}
	return (0); /* Not a built-in command */
}
/**
* print_environment - This command will the environment
*/
void print_environment(void)
{
	char **env = environ;
	/* Print all the strings in environ */
	while (*env)
	{
		printf("%s\n", *env);
		env++;
	}
}
