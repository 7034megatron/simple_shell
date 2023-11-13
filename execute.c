#include "main.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * execute_command - function to execute a command in a shell.
 * @tokens: pointer to the array of command and arguments.
 */
void execute_command(char *tokens[])
{
	pid_t pid = fork();

	if (pid == 0)
	{

		if (execve(tokens[0], tokens, environ) == -1)
		{
			perror("execve");
			exit(1);
		}
	}
	else if (pid < 0)
	{
		perror("fork");
	}
	else
	{
		wait(NULL);
	}
}
