#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

int main()
{
	char userInput[BUFFER_SIZE];
	char *cmmd;
	char *argm;

	while (1)
	{
		printf("$ ");
		fgets(userInput, BUFFER_SIZE, stdin);
		userInput[strcspn(userInput, "\n")] = '\0';

		cmmd = strtok(userInput, " ");
		argm = strtok(NULL, " ");

		if (cmmd != NULL)
		{
			if (strcmp(cmmd, "exit") == 0)
			{
				break;
			}
			else if (strcmp(cmmd, "cd") == 0)
			{
				if (argm != NULL)
				{
					if (chdir(argm) != 0)
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
						execvp(cmmd, &cmmd);
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
