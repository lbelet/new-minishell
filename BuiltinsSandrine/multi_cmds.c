#include "minishell.h"

void  ft_process_first(int fd_in, int fd_out, char *path_cmd, char **cmd, char **envp)
{
  dup2(fd_out, STDOUT_FILENO);
  close(fd_in);
  close(fd_out);
  execve(path_cmd, cmd, envp);
}

int  ft_process_middle(int fd_in, int fd_out, char *path_cmd, char **cmd, char **envp)
{
  dup2(fd_in, STDIN_FILENO);
  dup2(fd_out, STDOUT_FILENO);
  close(fd_in);
  close(fd_out);
  execve(path_cmd, cmd, envp);
  return (0);
}

void  ft_process_last(int fd_in, int fd_out, char *path_cmd, char **cmd, char **envp)
{
  dup2(fd_in, STDIN_FILENO);
  close(fd_in);
  close(fd_out);
  execve(path_cmd, cmd, envp);
}

int	ft_multi(int *pid, int len, int i, int k, char **split_pipe, int nbr_cmd, int **fd, char **envp, int *code_caractere)
{
	char **cmd;
	char *path_cmd;
	int j;

	pid[i] = fork();
	if (pid[i] < 0)
		return (0);
	if (pid[i] == 0)
	{
		cmd = ft_split_modif(split_pipe[i], ' ', code_caractere, len);
		path_cmd = ft_path(cmd[0]);
		if (path_cmd[0] == 'E')
		{
			printf("HERE Command '%s' not found\n", cmd[0]);
			free(cmd);
    		//free(pid);
			return (0);
		}
		j = 0;
		while (j < nbr_cmd - 1)
		{	
			if (j != k)
				close(fd[j][0]);
			if ( j != (k + 1))
				close(fd[j][1]);
			j++;
		}
		ft_process_middle(fd[k][0], fd[k + 1][1], path_cmd, cmd, envp);
		free(cmd);
		free(path_cmd);
	}
	return (0);
}

int ft_giant_pipex(char **split_pipe, int nbr_cmd, char **envp, int * code_caractere)
{
	int *pid;
	int **fd;
	int j;
	int k;
	char **cmd;
	char *path_cmd;
	int i;
	int len;

	j = 0;
	k = 0;
	i = 0;
	len = 0;
	pid = NULL;
	fd = malloc((nbr_cmd - 1) * sizeof(int*));
	while (j < nbr_cmd -1)
	{
		fd[j] = malloc(2 * sizeof(int));
		j++;
	}
   	pid = malloc(nbr_cmd * sizeof(int));
   	cmd = ft_split_modif(split_pipe[i], ' ', code_caractere, 0);
   	path_cmd = ft_path(cmd[0]);
	if (path_cmd[0] == 'E')
	{
		printf("Command '%s' not found\n", cmd[0]);
		free(cmd);
    	free(pid);
		return (0);
	}
  	j = 0;
	while (j < nbr_cmd - 1)
	{
		if (pipe(fd[j]) == -1)
      		return (0);
		j++;
	}
	if (i < 1)
	{
		pid[i] = fork();
		if (pid[i] < 0)
			return (0);
		if (pid[i] == 0) 
		{
			j = 0;
			while (j < nbr_cmd - 1)
			{
				if ( j != k)
				{
					close(fd[j][0]);
					close(fd[j][1]);
				}	
				j++;
			}
			ft_process_first(fd[k][0], fd[k][1], path_cmd, cmd, envp);
		}
		i++;
	}
    while (i < nbr_cmd - 1)
	{
		len += ft_strlen(split_pipe[i - 1]);
		ft_multi(pid, len, i, k, split_pipe, nbr_cmd, fd, envp, code_caractere);
		i++;
		k++;
	}
	if (i < nbr_cmd)
	{
		pid[i] = fork();
		if (pid[i] < 0)
			return (0);
		if (pid[i] == 0)
		{	
			j = 0;
			while (j < nbr_cmd - 1)
			{
				if (j != k)
				{
					close(fd[j][0]);
					close(fd[j][1]);	
				}
				j++;
			}
			len += ft_strlen(split_pipe[i - 1]);
			cmd = ft_split_modif(split_pipe[i], ' ', code_caractere, len);
			path_cmd = ft_path(cmd[0]);
			if (path_cmd[0] == 'E')
			{
				printf("Command '%s' not found\n", cmd[0]);
				free(cmd);
    			free(pid);
				return (0);
			}
			ft_process_last(fd[k][0], fd[k][1], path_cmd, cmd, envp);
		}
	}
	j = 0;
	while (j < nbr_cmd - 1) 
	{
    	close(fd[j][0]);
		close(fd[j][1]);
		j++;
	}
	j = 0;
	while (j < nbr_cmd)
	{
		waitpid(pid[j], NULL, 0);
		j++;
	}
	free(cmd);
//	free(path_cmd);
	free(pid);
	j = 0;
	while (j < nbr_cmd - 1)
	{
		free(fd[j]);
		j++;
	}
	free(fd);
	return (0);
}