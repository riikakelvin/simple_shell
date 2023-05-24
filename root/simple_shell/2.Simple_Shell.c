#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define BUFFER_SIZE 2024
#define TOKEN_DELIMITERS " "

int main(void)
{
	char *cmmd;
	char *argm;
	char *userInput;
	char input[BUFFER_SIZE];
	pid_t pid;

	while (1)
	{
		printf("$ ");
		fgets(input, BUFFER_SIZE, stdin);

		input[strcspn(input, "\n")] = '\0';

		if (strcmp(input, "exit") == 0)
			break;

		pid = fork();

		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			execlp("/bin/sh", "/bin/sh", "-c", input, NULL);

			perror("execvp");
			exit(EXIT_FAILURE);
		}
		else
		{
			wait(NULL);
		}
	}

	return (0);

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
