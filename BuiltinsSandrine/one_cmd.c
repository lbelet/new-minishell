#include "minishell.h"

void  ft_process_onlyone(char *path_cmd, char **cmd, char **envp)
{
  execve(path_cmd, cmd, envp);
}

int ft_process_one_classic(int *pid, char **cmd, char **envp)
{
	char *path_cmd;

	path_cmd = ft_path(cmd[0]);
	if (path_cmd[0] == 'E')
	{
		printf("Command %s not found\n", cmd[0]);
		return (0);
	}
	if (ft_strncmp(cmd[0], "echo", 4) != 0)
	{
    	pid[0] = fork();
        if (pid[0] < 0)
        	return (0);
    	if (pid[0] == 0)
            ft_process_onlyone(path_cmd, cmd, envp);
    	waitpid(pid[0], NULL, 0);
	}
	free(cmd);
    free(pid);
	free(path_cmd);
	return (0);
}

int ft_process_one_nosplit(int *pid, char **split_pipe, int *code_caractere, char **envp)
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
	pid[0] = fork();
	if (pid[0] < 0)
        return (0);
	if (pid[0] == 0)
	{
		fd_infile = open(ft_substr(str[0], 1, ft_strlen(str[0]) - 1), O_RDONLY);
		dup2(fd_infile, STDIN_FILENO);
		close(fd_infile);
		execve(path_cmd, cmd_infile, envp);
	}
	waitpid(pid[0], NULL, 0);
	return (0);
}

int ft_process_one_split(int *pid, char **split_pipe, int *code_caractere, char **envp)
{
	int i;
	int fd_infile;
	int nbr_cmd;
	char **str;
	char **cmd_infile;
	char *path_cmd;

	i = 0;
	nbr_cmd = 0;
	str = ft_split_modif(split_pipe[0], ' ', code_caractere, 0);
	while (str[i])
	{
		i++;
	}
	cmd_infile = malloc((i - 1) * sizeof(char *));
	while (nbr_cmd < i - 2)
	{
		cmd_infile[nbr_cmd] = ft_strdup(str[nbr_cmd + 2]);
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
	pid[0] = fork();
	if (pid[0] < 0)
        return (0);
	if (pid[0] == 0)
	{
		fd_infile = open(str[1], O_RDONLY);
		dup2(fd_infile, STDIN_FILENO);
		close(fd_infile);
		execve(path_cmd, cmd_infile, envp);
	}
	waitpid(pid[0], NULL, 0);
	return (0);
}

int ft_one(char **split_pipe, char **envp, int *code_caractere)
{
	int *pid;
	char **cmd;

	pid = NULL;
	pid = malloc(sizeof(int));
    cmd = ft_split_modif(split_pipe[0], ' ', code_caractere, 0);
    execute_inbuilt(cmd);
	if (cmd[0][0] == '<' && !cmd[0][1])
		ft_process_one_split(pid, split_pipe, code_caractere, envp);
	if (cmd[0][0] == '<' && cmd[0][1])
		ft_process_one_nosplit(pid, split_pipe, code_caractere, envp);
	if (cmd[0][0] != '<')
		ft_process_one_classic(pid, cmd, envp);
    return (0);
}
