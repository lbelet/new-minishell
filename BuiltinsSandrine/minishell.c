#include "minishell.h"

void ft_exec_cmd(char *str, char **envp)
{
	int *code_caractere;
	char **split_pipe;
	int nbr_cmd;

	nbr_cmd = 0;
	code_caractere = ft_code_caractere(str);
    split_pipe = ft_split_modif(str, '|', code_caractere, 0);
    while (split_pipe[nbr_cmd])
    	nbr_cmd++;
    if (nbr_cmd == 1)
    {
        ft_one(split_pipe, envp, code_caractere);         
    }
	if (nbr_cmd >= 2)
	{
		ft_giant_pipex(split_pipe, nbr_cmd, envp, code_caractere);
	}
}

int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;
    char *str;

    while (42)
    {
        define_input_signals();
        str = readline("prompt> ");
        if (str == NULL)//CTRL+D
            break;
        add_history(str);
		ft_exec_cmd(str, envp);
		free(str);      
    }
    return (0);
}