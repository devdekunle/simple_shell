#include "main.h"

/**
 * findpath - find the full path of an executable
 *
 * @cmnd: The command/executable
 *
 * Return: the full path of the executable
 */

char *findpath(char *cmnd)
{
int i, q, j;
char *token, *ret, *path[100], *p = _getenv("PATH");
char appending[20] = "/", *append = _strcat(appending, cmnd);

i = 0;
token = strtok(p, ":");
while (token)
{
	path[i] = strdup(token);
	token = strtok(NULL, ":");
	i++;
}
path[i] = NULL;
i = j = 0;
ret = malloc(sizeof(char) * 100);
while (path[i] != NULL)
{
	path[i] = _strcat(path[i], append);
	q = access(path[i], F_OK);
	if (q == 0)
	{
		j = i;
		ret = _strcpy(ret, path[i]);
		break;
	}
	i++;
}
i = 0;
while (path[i] != NULL)
{
	free(path[i]);
	i++;
}
if (j)
	return (ret);
return (NULL);
}
