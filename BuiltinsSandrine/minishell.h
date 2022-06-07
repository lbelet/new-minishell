#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdbool.h>
#include "./libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stddef.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdarg.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <limits.h>
#include <dirent.h>

/* TRANSPORT OF ENV_VARIABLES env var */
typedef struct s_env
{
    char    **envp;
    char    **env_var;
    char    *pwd;
    char    *oldpwd;
}          t_env;

void    display_prompt(int num);
void    define_input_signals(void);
int    echo(char **cmd_test);
int    execute_inbuilt(char **cmd_test);
int *ft_code_caractere(char *str);
void  ft_process_onlyone(char *path_cmd, char **cmd, char **envp);
int ft_process_one_classic(int *pid, char **cmd, char **envp);
int ft_process_one_nosplit(int *pid, char **split_pipe, int *code_caractere, char **envp);
int ft_process_one_split(int *pid, char **split_pipe, int *code_caractere, char **envp);
int ft_one(char **split_pipe, char **envp, int *code_caractere);
void  ft_process_first(int fd_in, int fd_out, char *path_cmd, char **cmd, char **envp);
int  ft_process_middle(int fd_in, int fd_out, char *path_cmd, char **cmd, char **envp);
void  ft_process_last(int fd_in, int fd_out, char *path_cmd, char **cmd, char **envp);
int	ft_multi(int *pid, int len, int i, int k, char **split_pipe, int nbr_cmd, int **fd, char **envp, int *code_caractere);
int ft_giant_pipex(char **split_pipe, int nbr_cmd, char **envp, int * code_caractere);
char **ft_get_path(void);
char *ft_path(char *str);
void  ft_process_onlyone(char *path_cmd, char **cmd, char **envp);
void  ft_process_first(int fd_in, int fd_out, char *path_cmd, char **cmd, char **envp);
int  ft_process_middle(int fd_in, int fd_out, char *path_cmd, char **cmd, char **envp);
void  ft_process_last(int fd_in, int fd_out, char *path_cmd, char **cmd, char **envp);
int ft_multiple_pipes(int i, int j, int *pid, int nbr_cmd, char **split_pipe, char **envp);
int ft_multiple_pipes_bis(int i, int j, int *pid, int nbr_cmd, char **split_pipe, char **envp);
int *ft_quote_place(char *str);
int ft_nbr_quote(char *str);
char **ft_parsing_quote(char *str);
char **ft_split_modif(char const *s, char c, int *code_caractere, int len);



#endif
