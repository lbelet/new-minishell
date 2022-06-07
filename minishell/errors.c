#include "minishell.h"

int ft_cmd_error(char *path_cmd, char **cmd_infile, int *pid)
{
	if (path_cmd[0] == 'E')
	{
		printf("Command %s not found\n", cmd_infile[0]);
		free(cmd_infile);
   		free(pid);
		return (0);
	}
	else
		return (1);
}