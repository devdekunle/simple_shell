#include "main.h"

/**
 * shell - Inbuilt shell
 *
 * @env: environment variable
 *
 * Return: (0) always success
 */

int shell(char **env)
{
	ssize_t read_line;
	char *token, *buffer, *path, *ret, *args[100], *envp[100];
	size_t n;
	int i, k, status, terminal;
	pid_t pid;
	struct stat st;

	i = 0;
	while(env[i])
	{
		envp[i] = env[i];
		i++;
	}
	envp[i] = NULL;
	read_line = n = 0;
	token = buffer = path = ret = NULL;
	terminal = 1;
	while (terminal)
	{
		i = 0;
		terminal = isatty(STDIN_FILENO);
		if (terminal)
		{
			write(STDOUT_FILENO, "($) ", 4);
			read_line = getline(&buffer, &n, stdin);
		}
		if (read_line == -1)
		{
			printf("logout\n");
			free(buffer);
			if (ret != NULL)
				free(ret);
			return (0);
		}
		if (_strcmp(buffer, "\n") == 0)
			continue;
		token = strtok(buffer, "\n");
		token = strtok(token, " ");

		while (token)
		{
			args[i] = token;
			token = strtok(NULL, " ");
			i++;
		}
		args[i] = NULL;
		if (_strcmp(args[0], "exit") == 0)
		{
			free(buffer);
			if (ret != NULL)
				free(ret);
			exit(EXIT_SUCCESS);
		}
		if ((_strcmp(args[0], "env") == 0))
		{	_print_env(env);
			continue;
		}

		if (stat(args[0], &st) == 0)
			path = args[0];
		else
		{
			ret = findpath(args[0]);
			path = ret;
		}

		if (path == NULL)
		{
			dprintf(STDERR_FILENO, "./hsh: 1:%s: not found\n", args[0]);
			continue;
		}
		pid = fork();
		if (pid == 0)
		{
			k = execve(path, args, envp);
			if (k == -1)
				dprintf(STDERR_FILENO, "./hsh: 1:%s: not found\n", args[0]);
		}
		else
			wait(&status);
	}
	free(buffer);
	free(ret);
	return (0);
}
