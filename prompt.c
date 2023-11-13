#include "main.h"
/**
* display_prompt - display the prompt required
* @prompt: pointer to a prompt.
* Return: nothing
*/
void display_prompt(const char *prompt)
{
	write(STDOUT_FILENO, prompt, strlen(prompt));
}
