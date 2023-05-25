#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#define BUFFER_SIZE 1020
#define TOKEN_DELIMITERS ","

int main(void)
{
	char input[BUFFER_SIZE];
	pid_t pid;

	while (1)
	{
		printf("$ ");
		fgets(input, BUFFER_SIZE, stdin);

		input[strcspn(input, "\n")] = '\0';
		if (strcmp(input, "exit") == 0)
			{ break;
			}
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
		{wait(NULL);
		}
	}
	return (0);
}
