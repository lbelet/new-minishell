#include "minishell.h"

char **ft_get_path(void)
{
    const char *path;
    char **tab_path;

    path = getenv("PATH");
    tab_path = ft_split(path, ':');
    return (tab_path);
}

char *ft_path(char *str)
{
    int i;
    char *path_cmd;
    char *path_cmd_final;
    char **tab_path;

    i = 0;
    tab_path = ft_get_path();
    while (tab_path[i])
    {
        path_cmd = ft_strjoin(tab_path[i], "/");
        path_cmd_final = ft_strjoin(path_cmd, str);
        free(path_cmd);
        if (open(path_cmd_final, O_RDONLY) < 0)
        {
            free(path_cmd_final);
            i++;
            if (!tab_path[i])
            {
                return ("ERROR");
            }
        }
        else
            break;
    }
    return (path_cmd_final);
}


