#include "minishell.h"
int ft_check_builtins(char **cmd)
{
    if (ft_strncmp(cmd[0], "echo", 4) != 0)
        return (0);
    return (1);
}

int    echo(char **cmd_test)
{
    int i;

    if (ft_strncmp(cmd_test[1], "-n", 2) == 0 && !cmd_test[1][2])
    {
        i = 2;
        while (cmd_test[i] && cmd_test[i + 1])
        {
            printf("%s ", cmd_test[i]);
            i++;
        }
        printf("%s", cmd_test[i]);
    }
    else
    {
        i = 1;
        while (cmd_test[i] && cmd_test[i + 1])
        {
            printf("%s ", cmd_test[i]);
            i++;
        }
        printf("%s\n", cmd_test[i]);
    }
    return (EXIT_SUCCESS);
}

int    execute_inbuilt(char **cmd_test)
{
    if ((ft_strncmp(cmd_test[0], "echo", 4)) == 0)
    {
        echo(&(cmd_test[0]));
        return (1);
    }
    /*
    if (ft_strcmp(cmd[0], "export") == 0)
        return (export(cmd));
    if (strncmp(cmd[0], "env", 3) == 0)
    {
        env(&(cmd[0]));
        return (0);
    }
    if (ft_strcmp(cmd[0], "cd") == 0)
        return (cd(cmd));
    if (ft_strcmp(cmd[0], "unset") == 0)
        return (unset(cmd));
    if (ft_strcmp(cmd[0], "pwd") == 0)
        return (pwd());
    if (ft_strcmp(cmd[0], "exit") == 0)
        return (exit_inbuilt(cmd));
     */
   return (0);
}