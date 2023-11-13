#include "main.h"
#include <stdio.h>
/**
 * search_path - Search for the full path of a command.
 * @command: The command to search for in the PATH.
 *
 * Return: The full path of the command if found, or NULL if not found.
 * @token: Token used in strtok function to tokenize the PATH.
 * @path_copy: Duplicate of the PATH variable.
 */
char *check_path(const char *command, char *token, char *path_copy);
char *search_path(const char *command)
{
	const char *path = getenv("PATH");
	char *path_copy = "", *full_path, *token = "";

	if (path == NULL || command == NULL)
		return (NULL);
	path_copy = strdup(path);
	if (path_copy == NULL)
		return (NULL);
	full_path = check_path(command, token, path_copy);
	free(path_copy);
	return (full_path);
}
/**
 * check_path - Check each directory in the PATH.
 * @command: The command to search for in each directory.
 * @token: Token used in strtok function to tokenize the PATH.
 * @path_copy: Duplicate of the PATH variable.
 *
 * Return: The full path of the command if found, or NULL if not found.
 */
char *check_path(const char *command, char *token, char *path_copy)
{
	char *full_path = NULL;
	struct stat info;

	token = strtok(path_copy, ":");
	while (token != NULL)
	{
		char *directory = strdup(token);

		if (directory != NULL)
		{
			size_t dir_len = strlen(directory);

			if (dir_len > 0 && directory[dir_len - 1] != '/')
			{
				directory = realloc(directory, dir_len + 2);
				strcat(directory, "/");
			}
			full_path = (char *)malloc(dir_len + strlen(command) + 1);
			if (full_path != NULL)
			{
				strcpy(full_path, directory);
				strcat(full_path, command);
				if (stat(full_path, &info) == 0)
				{
					free(directory);
					return (full_path);
				}
				free(full_path);
			}
			free(directory);
		}
		token = strtok(NULL, ":");
	}
	return (NULL); /* Return NULL if the command is not found in any path */
}
/**
 * _strncmp - Compare two strings up to a specified number of characters.
 * @s1: The first string to compare.
 * @s2: The second string to compare.
 * @n: The maximum number of characters to compare.
 *
 * Return: 0
 */
int _strncmp(char *s1, char *s2, size_t n)
{
	while (*s1 && *s2 && n > 0)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		n--;
		s1++;
		s2++;
	}
	return (0);
}
