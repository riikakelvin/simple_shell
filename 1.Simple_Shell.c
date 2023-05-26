#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define BUFFER_SIZE 2024

int main(void)
{
	char command[BUFFER_SIZE];
	pid_t child_pid;

	while (1)
	{
	printf("$ ");

	if (fgets(command, BUFFER_SIZE, stdin) == NULL)
	{
		printf("\n");
		break;
	}
	command[strcspn(command, "\n")] = '\0';

	child_pid = fork();

	if (child_pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
	else if (child_pid == 0)
		{
			if (execlp(command, command, NULL) == -1)
				{
				perror("execlp");
				exit(EXIT_FAILURE);
				}
		}
		else
		{
			int status;

			waitpid(child_pid, &status, 0);
			if (status != 0)
				{
				printf("Command not found: %s\n", command);
				}
		}
	}
	return (EXIT_SUCCESS);
}
