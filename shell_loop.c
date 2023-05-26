#include "shell.h"
/**
 * hsh - the main program's shell loop
 * @info: the parameter & return info struct
 * @av: the argument vector from main function
 * Return: 0 success, 1 on failure
 */
int hsh(info_t *info, char **av)
{
	ssize_t t = 0;
	int builtin_retu = 0;

	while (t != -1 && builtin_retu != -2)
	{
		clear_info(info);
		if (interactive(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		t = get_input(info);
		if (t != -1)
		{
			set_info(info, av);
			builtin_retu = find_builtin(info);
			if (builtin_retu == -1)
				find_cmd(info);
		}
		else if (interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_retu);
}

/**
 * find_builtin - searches for a builtin command
 * @info: the parameter & return info struct
 * Return: -1 when builtin is not found,
 *	0 for builtin executed successfully,
 *	1 for builtin found but exec unsuccessful,
 *	2 for builtin signaling exit function
 */
int find_builtin(info_t *info)
{
	int k, built_in_retu = -1;
	builtin_table builtintbl[] = {
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"exit", _myexit},
		{"env", _myenv},
		{"history", _myhistory},
		{"help", _myhelp},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (k = 0; builtintbl[k].type; k++)
		if (_strcmp(info->argv[0], builtintbl[k].type) == 0)
		{
			info->line_count++;
			built_in_retu = builtintbl[i].func(info);
			break;
		}
	return (built_in_retu);
}

/**
 * find_cmd - searches for a cmd in path
 * @info: the parameter & return info struct
 * Return: void
 */
void find_cmd(info_t *info)
{
	char *path = NULL;
	int t, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (t = 0, k = 0; info->arg[t]; t++)
		if (!is_delim(info->arg[t], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH=")
					|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * fork_cmd - forks an exec thread to run a command
 * @info: the parameter & return info struct
 * Return: void
 */
void fork_cmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission Not Granted\n");
		}
	}
}

