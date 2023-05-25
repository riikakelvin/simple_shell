#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define BUFFER_SIZE 1020

int main(void)
{
	char cmmd[BUFFER_SIZE];
	pid_t pid;
	char *env[] = {NULL};
	char *args[2];

	while (1)
	{
		printf("$");

		if (fgets(cmmd, BUFFER_SIZE, stdin) == NULL)
		{
			printf("\n");
			break;
		}

		cmmd[strcspn(cmmd, "\n")] = '\0';

		if (access(cmmd, X_OK) == -1)
		{
			printf("$: command not found\n");
			continue;
		}

		pid = fork();

		if (pid < 0)
		{
			printf("Fork failed\n");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			args[0] = cmmd;
			args[1] = NULL;
			if (execve(cmmd, args, env) == -1)
			{
				printf("Execution failed\n");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			wait(NULL);
		}
	}

	return (0);
}
