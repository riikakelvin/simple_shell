#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

int main()
{
	char userInput[BUFFER_SIZE];
	char *command;
	char *argument;

	while (1)
	{
		printf("$ ");
		fgets(userInput, BUFFER_SIZE, stdin);
		userInput[strcspn(userInput, "\n")] = '\0';

		command = strtok(userInput, " ");
		argument = strtok(NULL, " ");

		if (command != NULL)
		{
			if (strcmp(command, "exit") == 0)
			{
				break;
			}
			else if (strcmp(command, "cd") == 0)
			{
				if (argument != NULL)
				{
					if (chdir(argument) != 0)
					{
						printf("Error: failed to change directory\n");
					}
					else
					{
						printf("Error: missing argument for ‘cd’\n");
					}
				}
				else
				{
					int pid = fork();
					if (pid == 0)
					{
						execvp(command, &command);
						printf("Error: command not found");
						exit(EXIT_FAILURE);
					}
					else if (pid > 0)
					{
						wait(NULL);
					}
					else
					{
						printf("Error: fork failed\n");
					}
				}
			}
		}
	}
	return (0);
}
