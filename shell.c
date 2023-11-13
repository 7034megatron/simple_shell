#include "main.h"

int parse_commands(char *token, char *buf, char **commands, char *delim);
void run_commands(char **tokens, char *shell_name);
/**
 * run_shell - Run a simple shell that reads and executes commands.
 * @prompt: The shell prompt to display.
 * @shell_name: The name of the shell program.
 *
 * Return: The exit status of the shell.
 */
int run_shell(const char *prompt, char *shell_name)
{
	size_t n = 10;
	char *buf = malloc(sizeof(char) * n);
	ssize_t read_bytes;
	char *token = "";
	char *tokens[64];
	int i = 0;
	int exit_status = 0;
	int num_commands = 0;
	char *commands[64];
	int j = 0;
	char *command;
	int exit = 0;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			display_prompt(prompt);
		read_bytes = getline(&buf, &n, stdin);
		if (read_bytes <= 0)
			break;
		num_commands = parse_commands(token, buf, commands, ";");
		for (j = 0; j < num_commands; j++)
		{
			command = commands[j];
			if (_strncmp(command, "env", 3) == 0)
			{
				print_environment();
				continue;
			}
			i =  parse_commands(token, command, tokens, " \t\n");
			if (i < 1)
				continue;
			tokens[i] = NULL;
			if (_strncmp(tokens[0], "exit", 4) == 0)
			{
				if (tokens[1] != NULL)
					exit_status = atoi(tokens[1]);
				exit = 1;
				break;
			}
			run_commands(tokens, shell_name);
		}
		if (exit)
			break;
	}
	free(buf);
	return (exit_status);
}
/**
 * run_commands - Execute commands based on the parsed tokens.
 * @tokens: Array of tokens representing a command.
 * @shell_name: The name of the shell program.
 */
void run_commands(char **tokens, char *shell_name)
{
	/* Check if its changing the directory */
	if (_strncmp(tokens[0], "cd", 2) == 0)
	{
		if (tokens[1] != NULL)
		{
			if (chdir(tokens[1]) != 0)
				perror(shell_name);
		}
		else
		{
			char *home_dir = getenv("HOME");

			if (chdir(home_dir) != 0)
				perror(shell_name);
		}
	}
		/* Check if the its an absolute path */
	else if (tokens[0][0] == '/' || tokens[0][0] == '.')
	{
		if (access(tokens[0], X_OK) == 0)
		{
			execute_command(tokens);
		}
		else
		{
			perror(shell_name);
		}
	}
	else
		{
			tokens[0] = search_path(tokens[0]);
			if (tokens[0] != NULL)
			{
				execute_command(tokens);
			}
			else
			{
				perror(shell_name);
			}
		}
}
/**
 * parse_commands - Tokenize string to commands using a specified delimiter.
 * @token: Token used in strtok function.
 * @buf: The input buffer to be tokenized.
 * @commands: An array to store the tokens (commands).
 * @delim: The delimiter used for tokenization.
 *
 * Return: The number of commands found.
 */
int parse_commands(char *token, char *buf, char **commands, char *delim)
{
	int num_commands = 0;

	token = strtok(buf, delim);
	while (token != NULL)
	{
		commands[num_commands] = token;
		num_commands++;
		token = strtok(NULL, delim);
	}
	return (num_commands);
}
