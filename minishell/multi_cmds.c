#include "minishell.h"

void  ft_process_first(int fd_in, int fd_out, char *path_cmd, char **cmd, char **envp)
{
  dup2(fd_out, STDOUT_FILENO);
  close(fd_in);
  close(fd_out);
  execve(path_cmd, cmd, envp);
}

int ft_process_first_nosplit(int fd_in, int fd_out, int *pid, char **split_pipe, int *code_caractere, char **envp)
{
	int i;
	int nbr_cmd;
	int fd_infile;
	char **str;
	char **cmd_infile;
	char *path_cmd;

	nbr_cmd = 0;
	i = 0;
	str = ft_split_modif(split_pipe[0], ' ', code_caractere, 0);
	while (str[i])
	{
		i++;
	}
	cmd_infile = malloc((i) * sizeof(char *));
	while (nbr_cmd < i - 1)
	{
		cmd_infile[nbr_cmd] = ft_strdup(str[nbr_cmd + 1]);
		nbr_cmd++;
	}
	cmd_infile[nbr_cmd] = NULL;
	path_cmd = ft_path(cmd_infile[0]);
	if (path_cmd[0] == 'E')
	{
		printf("Command %s not found\n", cmd_infile[0]);
		free(cmd_infile);
   		free(pid);
		return (0);
	}
	fd_infile = open(ft_substr(str[0], 1, ft_strlen(str[0]) - 1), O_RDONLY);
	dup2(fd_infile, STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	close(fd_infile);
	close(fd_in);
	close(fd_out);
	execve(path_cmd, cmd_infile, envp);
	return (0);
}

int ft_process_first_split(int fd_in, int fd_out, int *pid, char **cmd, char **envp)
{
	int i;
	int fd_infile;
	int nbr_cmd;
	char **cmd_infile;
	char *path_cmd;

	i = 0;
	nbr_cmd = 0;
	while (cmd[i])
	{
		i++;
	}
	cmd_infile = malloc((i - 1) * sizeof(char *));
	while (nbr_cmd < i - 2)
	{
		cmd_infile[nbr_cmd] = ft_strdup(cmd[nbr_cmd + 2]);
		nbr_cmd++;
	}
	cmd_infile[nbr_cmd] = NULL;
	path_cmd = ft_path(cmd_infile[0]);
	if (path_cmd[0] == 'E')
	{
		printf("Command %s not found\n", cmd_infile[0]);
		free(cmd_infile);
   		free(pid);
		return (0);
	}
	fd_infile = open(cmd[1], O_RDONLY);
	dup2(fd_infile, STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	close(fd_infile);
	close(fd_in);
	close(fd_out);
	execve(path_cmd, cmd_infile, envp);
	return (0);
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

int	ft_multi(int *pid, int i, int k, char **split_pipe, int nbr_cmd, int **fd, char **envp)
{
	char **cmd;
	char *path_cmd;
	int j;
	int l;

	pid[i] = fork();
	cmd = ft_split_modif(split_pipe[i], ' ', ft_code_caractere(split_pipe[i]), 0);
	l = 0;
	while (cmd[l])
	{
		ft_check_quote(cmd, l);
		l++;
	}
	path_cmd = ft_path(cmd[0]);
	if (path_cmd[0] == 'E')
	{
		printf("HERE Command '%s' not found\n", cmd[0]);
		free(cmd);
		return (0);
	}
	if (pid[i] < 0)
		return (0);
	if (pid[i] == 0)
	{
		if (ft_check_builtins(cmd) == 0)
		{
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
		else
		{
			j = 0;
			while (j < nbr_cmd - 1)
			{	
				close(fd[j][0]);
				if ( j != (k + 1))
					close(fd[j][1]);
				j++;
			}
			ft_execute_inbuilt_fd(fd[k + 1][1], cmd);
			exit(0);
		}
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
	int l;

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
	l = 0;
	while (cmd[l])
	{
		ft_check_quote(cmd, l);
		l++;
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
			if (cmd[0][0] == '<' && cmd[0][1])
				ft_process_first_nosplit(fd[k][0], fd[k][1], pid, split_pipe, code_caractere, envp);
			else if (cmd[0][0] == '<' && !cmd[0][1])
				ft_process_first_split(fd[k][0], fd[k][1], pid, cmd, envp);		
			else if (cmd[0][0] != '<')
			{
				if (ft_check_builtins(cmd) == 0)
				{
					path_cmd = ft_path(cmd[0]);
					if (ft_cmd_error(path_cmd, cmd, pid) == 0)
						return (0);
					ft_process_first(fd[k][0], fd[k][1], path_cmd, cmd, envp);
				}
				ft_execute_inbuilt_fd(fd[k][1], cmd);
				exit(0);
			}
		}
		i++;
	}
    while (i < nbr_cmd - 1)
	{
		len += ft_strlen(split_pipe[i - 1]);
		ft_multi(pid, i, k, split_pipe, nbr_cmd, fd, envp);
		i++;
		k++;
	}
	if (i < nbr_cmd)
	{
		len += ft_strlen(split_pipe[i - 1]);
		cmd = ft_split_modif(split_pipe[i], ' ', ft_code_caractere(split_pipe[i]), 0);
		l = 0;
		while (cmd[l])
		{
			ft_check_quote(cmd, l);
			l++;
		}
		path_cmd = ft_path(cmd[0]);
		pid[i] = fork();
		if (pid[i] < 0)
			return (0);
		if (pid[i] == 0)
		{	
			if (ft_check_builtins(cmd) == 0)
			{
				if (ft_cmd_error(path_cmd, cmd, pid) == 0)
					return (0);
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
				ft_process_last(fd[k][0], fd[k][1], path_cmd, cmd, envp);
			}
			else
			{
				j = 0;
				while (j < nbr_cmd - 1)
				{

					close(fd[j][0]);
					close(fd[j][1]);	
					j++;
				}
				execute_inbuilt(cmd);
				exit(0);
			}
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