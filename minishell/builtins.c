#include "minishell.h"
int ft_check_builtins(char **cmd)
{
    if (ft_strncmp(cmd[0], "echo", 4) == 0)
        return (1);
    else if (ft_strncmp(cmd[0], "exit", 4) == 0)
        return (1);
    else if (ft_strncmp(cmd[0], "pwd", 3) == 0)
        return (1);
    else if (ft_strncmp(cmd[0], "env", 3) == 0)
        return (1);
    else if (ft_strncmp(cmd[0], "cd", 2) == 0)
        return (1);
    else if (ft_strncmp(cmd[0], "export", 6) == 0)
        return (1);
    else if (ft_strncmp(cmd[0], "unset", 5) == 0)
        return (1);
    return (0);
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
// =====================================================================================

void    ft_free_str(char **str)
{
    free(*str);
    *str = NULL;
}

/*Frees allocated null-terminated string array*/
void    ft_free_str_array(char ***arr)
{
    int    i;

    i = 0;
    while (*arr && (*arr)[i])
    {
        ft_free_str(&(*arr)[i]);
        (*arr)[i] = NULL;
        i++;
    }
    free(*arr);
    *arr = NULL;
}

/*returns the size of an nullterminated array of strings*/
int    ft_str_arr_len(char **arr)
{
    int    i;

    i = 0;
    while (arr && arr[i])
        i++;
    return (i);
}

/* returns the value of the difference found in two strings, 0 if equal */
int    ft_strcmp(char *s1, char *s2)
{
    unsigned char    *buf1;
    unsigned char    *buf2;

    buf1 = (unsigned char *)s1;
    buf2 = (unsigned char *)s2;
    if (*buf1 != *buf2)
        return (*buf1 - *buf2);
    while (*buf1 && *buf2)
    {
        if (*buf1 != *buf2)
            return (*buf1 - *buf2);
        buf1++;
        buf2++;
    }
    if (*buf1 == '\0' && *buf2 != '\0')
        return (0 - *buf2);
    else if (*buf2 == '\0' && *buf1 != '\0')
        return (*buf1);
    return (0);
}

static char    *ft_get_var(t_env *envv, int i)
{
    char    **split;
    char    *var;

    split = ft_split(envv->env_var[i], '=');
    if (split == NULL)
        return (NULL);
    var = ft_strdup(split[0]);
    ft_free_str_array(&split);
    return (var);
}

static void    ft_del_var(t_env *envv, int i)
{
    int    j;

    ft_free_str(&envv->env_var[i]);
    j = i;
    while (envv->env_var[j + 1])
    {
        envv->env_var[j] = envv->env_var[j + 1];
        j++;
        if (envv->env_var[j + 1] == NULL)
            envv->env_var[j] = NULL;
        i = ft_str_arr_len(envv->env_var);
    }
}

static int    ft_inner_loop(char **argv, t_env *envv, int i, int k)
{
    char    *var;

    var = NULL;
    if (ft_strcmp(envv->env_var[i], argv[k]) == 0
        || ft_strcmp(envv->env_var[i], argv[k]) == 61)
    {
        var = ft_get_var(envv, i);
        if (var == NULL)
            return (EXIT_FAILURE);
        if (ft_strncmp(var, argv[k], ft_strlen(var) != 0)
            || ft_strncmp(var, argv[k], ft_strlen(argv[k]) != 0))
        {
            ft_free_str(&var);
            return (2);
        }
        ft_del_var(envv, i);
    }
    ft_free_str(&var);
    return (EXIT_SUCCESS);
}

static t_env    *_get_envv(t_env *envv)
{
    static t_env    *static_envv = NULL;

    if (envv == NULL)
        return (static_envv);
    static_envv = envv;
    return (static_envv);
}

void    set_envv(t_env *envv)
{
    _get_envv(envv);
}

t_env    *get_envv(void)
{
    return (_get_envv(NULL));
}

int    unset(char **argv)
{
    int        i;
    int        k;
    int        inner_out;
    t_env    *envv;

    k = 1;
    envv = get_envv();
    //envv = getenv(); a voir si remplacer get_envv par getenv????????
    if (argv[k] == NULL)
        return (EXIT_SUCCESS);
    while (argv[k])
    {
        i = 0;
        while (envv->env_var[i])
        {
            inner_out = ft_inner_loop(argv, envv, i, k);
            if (inner_out == 2)
                break ;
            else if (inner_out == EXIT_FAILURE)
                return (EXIT_FAILURE);
            i++;
        }
        k++;
    }
    return (EXIT_SUCCESS);
}

// =====================================================================================

static int    _get_err_code(int err_code, bool set_err_code)
{
    static int    static_err_code = 0;

    if (set_err_code)
        static_err_code = err_code;
    return (static_err_code);
}

/*void    set_err_code(int err_code)
{
    static bool    last_cmd_ctrlc = false;
    if (last_cmd_ctrlc)
    {
        last_cmd_ctrlc = false;
        return ;
    }
    if (err_code == 130)
        last_cmd_ctrlc = true;
    _get_err_code(err_code, true);
}*/

int    get_err_code(void)
{
    return (_get_err_code(0, false));
}

int    ft_issign(char c)
{
    if (c == '+' || c == '-')
        return (true);
    return (false);
}

int    ft_isspace(int c)
{
    if (c == ' ' || c == '\t' || c == '\n'
        || c == '\v' || c == '\f' || c == '\r')
        return (true);
    return (false);
}

long long   ft_atol(char *str)
{
    long long    n;
    int            is_negative;

    n = 0;
    is_negative = 1;
    while (ft_isspace(*str))
        str++;
    if (ft_issign(*str))
    {
        if (*str == '-')
            is_negative = -1;
        str++;
    }
    while (ft_isdigit(*str))
    {
        n = (n * 10) + (*str - '0');
        if (n < 0 && is_negative == -1)
            return (0);
        else if (n < 0 && is_negative == 1)
            return (-1);
        str++;
    }
//    if (ft_strcmp(str, "-9223372036854775808") == 0)
//        return (-9223372036854775808);
    return (n * is_negative);
}

static bool    is_valid_exit_arg(char *args[])
{
    int    i;
    int    j;

    i = 0;
    while (args && args[i])
    {
        j = 0;
        while (args[i][j])
        {
            if (ft_issign(args[i][j]))
                j++;
            if (!ft_isdigit(args[i][j]))
                return (false);
            j++;
        }
        i++;
    }
    return (true);
}

int    exit_inbuilt(char *args[])
{
    long long   exit_code;
    int        i;

    i = 1;
//    if (ft_strncmp(args[i], "exit", ft_strlen(args[i])) != 0)
//        return (EXIT_FAILURE);
    if (!args[1])
    {
        printf("exit\n");
        exit_code = 0;
        exit(exit_code);
        return (exit_code);
    }
    if (args[i])
        exit_code = ft_atol(args[i]);
    else
        exit_code = get_err_code();
    if (!is_valid_exit_arg(args + i) || ft_strlen(args[i]) > 20)
    {
        printf("exit: not a valid argument\n");
        exit_code = 255;
    }
    //else if (args[i] && args[++i])
    //{
    //    printf("exit: too many arguments\n");
    //    printf("exit\n");
    //    return (EXIT_FAILURE);
    //}
    printf("exit\n");
    exit(exit_code);
    return (exit_code);
}

// =====================================================================================

int    pwd(void)
{
    char    *cwd;

    cwd = NULL;
    cwd = getcwd(cwd, 0);
    if (cwd == NULL)
    {
        perror("Error");
        return (EXIT_FAILURE);
    }
    else
        printf("%s\n", cwd);
    return (EXIT_SUCCESS);
}

// ==========================================================================================

int ft_nbr_args(char **cmd_test)
{
    int i;
    int nbr_args;

    i = 1;
    nbr_args = 0;
    while (cmd_test[i])
    {
        i++;
        nbr_args++;
    }
    return (nbr_args);
}

char **ft_malloc_env(char **original)
{
    int i;
    char **sorted;

    i = 0;
    while (original[i])
        i++;
    sorted = malloc((i + 1) *sizeof(char *));
    sorted[i] = NULL;
    return (sorted);
}


char **ft_malloc_var(char **original)
{
    int i;
    char **sorted;

    i = 1;
    while (original[i])
        i++;
    sorted = malloc(i *sizeof(char *));
    sorted[i - 1] = NULL;
    return (sorted);
}

void ft_sort_alpha(char **sorted)
{
    int k;
    int j;
    char *tmp;

    k = 0;
    j = 0;
    while (sorted[k])
    {
        j = 0;
        while (sorted[j])
        {
            if (ft_strcmp(sorted[k], sorted[j]) < 0)
            {
                tmp = ft_strdup(sorted[k]);
                free(sorted[k]);
                sorted[k] = ft_strdup(sorted[j]);
                free(sorted[j]);
                sorted[j] = ft_strdup(tmp);
                free(tmp);
            }
            j++;
        }
        k++;
    }
}

void ft_printf_all(char **sorted)
{
    int i;

    i = 0;
    while (sorted[i])
    {
        printf("declare -x %s\n", sorted[i]);
        i++;
    }  
}

char  **ft_export(char **cmd_test, char **envp, char **args)
{
    int i;
    int j;
    char **envp_sorted;
    char **new_args;
//    static char **args = NULL;
    char **tmp;

    j = 0;
    i = 0;
    envp_sorted = ft_malloc_env(envp);
    if (!envp_sorted)
        return NULL;
    if (ft_nbr_args(cmd_test) == 0)
    {
        while (envp[i])
        {
            envp_sorted[i] = ft_strdup(envp[i]);
            i++;
        }
        ft_sort_alpha(envp_sorted);
        ft_printf_all(envp_sorted);
        if (args)
        {
            ft_sort_alpha(args);
            ft_printf_all(args);
        }
    }
    if (ft_nbr_args(cmd_test) > 0)
    {
        new_args = ft_malloc_var(cmd_test);
        if (!new_args)
            return NULL;
        while (i < ft_nbr_args(cmd_test))
        {
            new_args[i] = ft_strdup(cmd_test[i + 1]);
            i++;
        }
        if (!args)
        {
            ft_sort_alpha(new_args);
            args = ft_malloc_env(new_args);
            i = 0;
            while (new_args[i])
            {
                args[i] = ft_strdup(new_args[i]);
                printf("%s\n", args[i]);
                i++;
            }
        }
        else if (args[0])
        {
            tmp = ft_malloc_env(args);
            i = 0;
            while (args[i])
            {
                tmp[i] = ft_strdup(args[i]);
                free(args[i]);
                i++;
            }
            free(args);
            args = malloc((i + ft_nbr_args(cmd_test) + 1) * sizeof(char *));
            args[i + ft_nbr_args(cmd_test) + 1] = NULL;
            i = 0;
            while (tmp[i])
            {
                args[i] = ft_strdup(tmp[i]);
                i++;
            }
            while (j < ft_nbr_args(cmd_test))
            {
                args[i + j] = ft_strdup(cmd_test[j + 1]);
                j++;
            }
        }
    }
    return (args);
}

// ==========================================================================================

int ft_env(char **envp, char **args_in)
{
    int i;
    int j;

    j = 0;
    i = 0;
    while (envp[i])
    {
        printf("%s\n", envp[i]);
        i++;
    }
    if (args_in)
    {
        while (args_in[j])
        {
            printf("%s\n", args_in[j]);
            j++;
        }
    }
    
    return (0);
}

// ==========================================================================================

void ft_unset(char **cmd_test, char **args_in)
{
    int i;
    int j;

    i = 0;
    j = 0;
    if (!cmd_test[1])
        return;
    while (args_in[j])
        j++;
    while (args_in[i])
    {
        if (ft_strncmp(args_in[i], cmd_test[1], ft_strlen(cmd_test[1])) != 0)
            i++;
        else
        {
            args_in[i] = ft_strdup("zzzzzz");
            ft_sort_alpha(args_in);
            args_in[j - 1] = NULL;
            return ;
        }
    }
    return ;
}

// ==========================================================================================

int ft_cd(char **cmd_test, char **envp)
{
    int i;
    char **copy_env;
    char *temp;
    char *cwd;
    char *cwdbis;

    i = 0;
    cwd = NULL;
    cwdbis = NULL;
    while (envp[i])
        i++;
    copy_env = malloc((i + 1) * sizeof(char *));
    i = 0;
    while(envp[i])
    {
        copy_env[i] = ft_strdup(envp[i]);
        i++;
    }
    copy_env[i] = NULL;
    cwd = getcwd(cwd, 0);
    if (cmd_test[1])
        chdir(cmd_test[1]);
    else if (!cmd_test[1])
        chdir("/Users/lbelet");
    cwdbis = getcwd(cwdbis, 0);

    i = 0;
    while (copy_env[i])
    {
        if (ft_strncmp(copy_env[i], "PWD", 3) == 0)
        {
            temp = ft_strdup(copy_env[i]);
            free(copy_env[i]);
            copy_env[i] = ft_strdup("PWD=");
            copy_env[i] = ft_strjoin(copy_env[i], cwdbis);
        }
        if (ft_strncmp(copy_env[i], "OLDPWD", 6) == 0)
        {
            free(copy_env[i]);
            copy_env[i] = ft_strdup("OLDPWD=");
            copy_env[i] = ft_strjoin(copy_env[i], cwd);
        }
        i++;
    }
    i = 0;
    while (copy_env[i])
    {
        envp[i] = ft_strdup(copy_env[i]);
        i++;
    }
    return (0);
}

// ========================================================================================

void    execute_inbuilt(char **cmd_test, char **envp)
{
    static char **args_in = NULL;

    if ((ft_strncmp(cmd_test[0], "echo", 4)) == 0)
        echo(&(cmd_test[0]));
    if (ft_strncmp(cmd_test[0], "export", 6) == 0)
         args_in = ft_export(cmd_test, envp, args_in);
    if (strncmp(cmd_test[0], "env", 3) == 0)
        ft_env(envp, &(args_in[0]));
    if (ft_strncmp(cmd_test[0], "cd", 2) == 0)
        ft_cd(cmd_test, envp);
    if (ft_strcmp(cmd_test[0], "unset") == 0)
        ft_unset(cmd_test, &(args_in[0]));
    if (ft_strncmp(cmd_test[0], "pwd", 3) == 0)
        pwd();
    if ((ft_strncmp(cmd_test[0], "exit", 4)) == 0)
        exit_inbuilt(&(cmd_test[0]));
}