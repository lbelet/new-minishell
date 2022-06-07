#include "minishell.h"

//------------------------------ECHO-------------------------------------------
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
//-------------------------------------------------------------------------------
//------------------------------PWD---------------------------------------------
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
//--------------------------------------------------------------------------------
//----------------------------UNSET-----------------------------------------------
/*frees the given string and sets it to NULL*/
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
//-------------------------------------------------------------------------------
//-------------------------------ENV---------------------------------------------
int    env(char **argv)
{
    int        i;
    t_env    *envv;

    envv = get_envv();
    if (envv == NULL || envv->env_var == NULL)
        return (EXIT_FAILURE);
    if (argv != NULL && argv[1] != NULL)
    {
        if (access(argv[1], F_OK) == 0)//fonction autorisée
        {
            printf("env: %s: Premission denied\n", argv[1]);
            return (126);//command invoked cannot execute (permission problem or not an executable)
        }
        printf("env: %s: No such file or directory\n", argv[1]);
        return (127);//command not found
    }
    i = 0;
    while (envv->env_var && envv->env_var[i] != NULL)
    {
        if (printf("%s\n", envv->env_var[i++]) == 0)
            return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}

//-------------------------------------------------------------------------------
//---------------------------EXIT------------------------------------------------
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

long    ft_atol(const char *str)
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
    long    exit_code;
    int        i;

    i = 0;
    if (ft_strncmp(args[i], "exit", ft_strlen(args[i])) != 0)
        return (EXIT_FAILURE);
    i++;
    if (args[i])
        exit_code = ft_atol(args[i]);
    else
        exit_code = get_err_code();
    if (!is_valid_exit_arg(args + i) || ft_strlen(args[i]) > 19)
    {
        printf("exit: not a valid argument\n");
        exit_code = 255;
    }
    else if (args[i] && args[++i])
    {
        printf("exit: too many arguments\n");
        printf("exit\n");
        return (EXIT_FAILURE);
    }
    printf("exit\n");
    exit(exit_code);
    return (exit_code);
}
//-----------------------------------------------------------------------------
//---------------------------------CD------------------------------------------
/*
strdup for string arrays
arr: the array to copy
cpy: the copied array that gets returned
*/
char    **ft_str_arr_dup(char **arr)
{
    char    **cpy;
    int        i;

    if (arr == NULL)
        return (NULL);
    cpy = ft_calloc(ft_str_arr_len(arr) + 1, sizeof(*cpy));
    if (cpy == NULL)
        return (NULL);
    i = 0;
    while (arr[i])
    {
        cpy[i] = ft_strdup(arr[i]);
        i++;
    }
    return (cpy);
}
/*
this function is similar to realloc, but only for string-arrays
++ instead of malloc this uses calloc
-- it will create a new adress and free the old one of arr
if allocation of the new size fails arr will be freed
arr: adress of the array you want to realloc
size: number of elements you want to realloc
new: adress of the reallocated array of strings
*/
char    **ft_realloc_str_arr(char **arr, int size)
{
    char    **new;
    int        i;

    if (arr == NULL)
        return (NULL);
    new = ft_calloc(size + 1, sizeof(char *));
    if (new == NULL)
    {
        ft_free_str_array(&arr);
        return (NULL);
    }
    i = 0;
    while (size-- && arr && arr[i])
    {
        new[i] = ft_strdup(arr[i]);
        i++;
    }
    ft_free_str_array(&arr);
    return (new);
}
void    *ft_free(void **p)
{
    if (p == NULL)
        return (NULL);
    free(*p);
    *p = NULL;
    return (NULL);
}
/* Appends src to dst, frees dst and returns newly created string */
char    *ft_append(char **dst, char *src)
{
    char    *dst_buf;
    char    *appendet;
    int        appendet_len;

    if (dst == NULL)
        dst_buf = NULL;
    else
        dst_buf = *dst;
    appendet_len = ft_strlen(dst_buf) + ft_strlen(src);
    if (appendet_len == 0)
    {
        ft_free((void *)dst);
        return (NULL);
    }
    appendet = malloc((appendet_len + 1) * sizeof(*appendet));
    if (appendet == NULL)
        return (NULL);
    while (dst_buf && *dst_buf)
        *appendet++ = *dst_buf++;
    while (src && *src)
        *appendet++ = *src++;
    *appendet = '\0';
    ft_free((void *)dst);
    return (appendet - appendet_len);
}

/*
will append s2 to s1
will do nothing if s1 is NULL
it will ad the divider string between the strings
will free s1
*/
char    *ft_strstrjoin(char *s1, char *s2, char *divider)
{
    char    *out;
    int        i;
    int        j;

    if (!s1)
        return (NULL);
    i = 0;
    j = 0;
    s1 = ft_append(&s1, divider);
    out = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
    if (out == NULL)
        return (0);
    while (s1[i])
    {
        out[i] = s1[i];
        i++;
    }
    while (s2 && s2[j])
        out[i++] = s2[j++];
    out[i] = '\0';
    ft_free_str(&s1);
    return (out);
}
static void    get_env_var_value_utils(t_env *envv, char *var, char **value, int i)
{
    if (ft_strlen(*value) == 0 && ft_strcmp(var, "PWD") == 0)
    {
        if (ft_strlen(envv->pwd) == 0)
            *value = ft_calloc(1, sizeof (char));
        else
            *value = ft_strdup(envv->pwd);
    }
    else if (ft_strlen(*value) == 0 && ft_strcmp(var, "OLDPWD") == 0)
    {
        if (ft_strlen(envv->oldpwd) == 0)
            *value = ft_calloc(1, sizeof (char));
        else
            *value = ft_strdup(envv->oldpwd);
    }
    else if (envv->env_var[i] == NULL && *value == NULL)
        *value = ft_calloc(1, sizeof(char));
}
/*
 * @brief  get value of a specific variable from env_var
 * @note  similar to getenv but uses our env_var instead of envp
 * @param  *envv: the t_env struct
 * @param  *var: the variable you are searching for without the '='
 * @retval the maloced value that was found, empty string if not found
 * * , NULL if error occured
*/
char    *get_env_var_value(t_env *envv, char *var)
{
    int        i;
    char    *value;

    value = NULL;
    i = 0;
    while (envv && envv->env_var && envv->env_var[i] != NULL)
    {
        if (ft_strcmp(var, envv->env_var[i]) == -61)
        {
            value = ft_strchr(envv->env_var[i++], '=') + 1;
            if (ft_strlen(value) == 0)
                value = ft_calloc(1, sizeof (char));
            else
                value = ft_strdup(value);
            break ;
        }
        else if (ft_strcmp(var, envv->env_var[i++]) == 0)
        {
            value = ft_calloc(1, sizeof (char));
            break ;
        }
    }
    get_env_var_value_utils(envv, var, &value, i);
    return (value);
}

/*
will create envv by duplicating envp into t_env *envv
everything except envp inside t_env is allocated
*/
t_env    *init_envv(char **envp)
{
    t_env    *envv;

    envv = ft_calloc(1, sizeof(t_env));
    if (envv != NULL && envp != NULL && *envp != NULL)
    {
        envv->envp = envp;
        envv->env_var = ft_str_arr_dup(envp);
        envv->pwd = get_env_var_value(envv, "PWD");
        envv->oldpwd = get_env_var_value(envv, "OLDPWD");
        if (envv->env_var != NULL && envv->pwd != NULL && envv->oldpwd != NULL)
            return (envv);
    }
    return (NULL);
}

/*
will free all allocated values of t_env and set them to NULL
*/
void    free_envv(t_env *envv)
{
    envv->envp = NULL;
    ft_free_str_array(&envv->env_var);
    ft_free_str(&envv->pwd);
    ft_free_str(&envv->oldpwd);
    free(envv);
}

/**
 * @brief  will reinitiate env_var if all values got unset
 * @note
 * @param  *envv: the t_env struct
 * @param  **argv: the first variable that gets exported into the empty env_var
 * @retval either EXIT_SUCCESS or EXIT_FAILURE
 */
int    reinit_env_var(t_env *envv, char **argv)
{
    if (*envv->env_var == NULL)
    {
        envv->env_var = ft_realloc_str_arr(envv->env_var, 2);
        if (envv->env_var == NULL)
            return (EXIT_FAILURE);
        envv->env_var[0] = ft_strdup(argv[1]);
        if (envv->env_var[0] == NULL)
            return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}
static char    *find_home(t_env *envv)
{
    char    *path;

    if (envv->env_var == NULL)
        return (NULL);
    path = get_env_var_value(envv, "HOME");
    if (ft_strlen(path) == 0)
    {
        printf("cd: HOME not set\n");
        ft_free_str(&path);
    }
    return (path);
}

static void    ft_update_env_var(t_env *envv, char *var, char *value)
{
    int    i;

    i = 0;
    if (ft_strcmp(var, "OLDPWD") == 0)
    {
        ft_free_str(&envv->oldpwd);
        envv->oldpwd = ft_strdup(envv->pwd);
    }
    if (ft_strcmp(var, "PWD") == 0)
    {
        ft_free_str(&envv->pwd);
        envv->pwd = ft_strdup(value);
    }
    while (envv->env_var && envv->env_var[i])
    {
        if (ft_strcmp(envv->env_var[i], var) == 0
            || ft_strcmp(envv->env_var[i], var) == 61)
        {
            ft_free_str(&envv->env_var[i]);
            envv->env_var[i] = ft_strstrjoin(ft_strdup(var), value, "=");
            return ;
        }
        i++;
    }
}

static int    ft_exit_cd(char **cwd, int exit_status)
{
    ft_free_str(cwd);
    if (exit_status == EXIT_SUCCESS)
        return (EXIT_SUCCESS);
    else
    {
        perror("Error");
        return (EXIT_FAILURE);
    }
}

static int    ft_cd_home(t_env *envv)
{
    char    *home_path;
    char    *cwd;

    cwd = NULL;
    home_path = find_home(envv);
    if (home_path == NULL)
        return (EXIT_FAILURE);
    if (chdir(home_path) != 0)
    {
        ft_free_str(&home_path);
        return (ft_exit_cd(&cwd, EXIT_FAILURE));
    }
    ft_update_env_var(envv, "OLDPWD", envv->pwd);
    cwd = getcwd(cwd, 0);
    ft_update_env_var(envv, "PWD", cwd);
    ft_free_str(&home_path);
    if (envv->pwd == NULL || envv->oldpwd == NULL)
        return (ft_exit_cd(&cwd, EXIT_FAILURE));
    return (ft_exit_cd(&cwd, EXIT_SUCCESS));
}

int    cd(char **cmd_test)
{
    char    *cwd;
    DIR        *directory;
    t_env    *envv;

    envv = get_envv();
    if (cmd_test == NULL || envv == NULL)
        return (EXIT_FAILURE);
    if (cmd_test[1] == NULL)
        return (ft_cd_home(envv));
    cwd = NULL;
    directory = opendir(cmd_test[1]);
    if (directory == NULL)
        return (ft_exit_cd(&cwd, EXIT_FAILURE));
    else if (closedir(directory) != 0)
        return (ft_exit_cd(&cwd, EXIT_FAILURE));
    else if (chdir(cmd_test[1]) != 0)
        return (ft_exit_cd(&cwd, EXIT_FAILURE));
    ft_update_env_var(envv, "OLDPWD", envv->pwd);
    cwd = getcwd(cwd, 0);
    ft_update_env_var(envv, "PWD", cwd);
    if (envv->pwd == NULL || envv->oldpwd == NULL)
        return (ft_exit_cd(&cwd, EXIT_FAILURE));
    return (ft_exit_cd(&cwd, EXIT_SUCCESS));
}
//-----------------------------------------------------------------------------
//------------------------------EXECUTION--------------------------------------

int    execute_inbuilt(char **cmd_test)// char **env)
{
    if ((ft_strncmp(cmd_test[0], "echo", 4)) == 0)
    {
        echo(&(cmd_test[0]));
        return (1);
    }
    /*
    if (ft_strcmp(cmd[0], "export") == 0)
        return (export(cmd));*/
    
    if ((ft_strncmp(cmd_test[0], "env", 3)) == 0)
    {
        env(&(cmd_test[0]));
        return (1);
    }
    
    if ((ft_strncmp(cmd_test[0], "cd", 2)) == 0)
        return (cd(cmd_test));
    
    if ((ft_strncmp(cmd_test[0], "unset", 5)) == 0)
    {
        //return (unset(cmd));
        unset(&(cmd_test[0]));
        return (1);
    }
    
    if ((ft_strncmp(cmd_test[0], "pwd", 3)) == 0)
        return (pwd());
    
    if ((ft_strncmp(cmd_test[0], "exit", 4)) == 0)
    {
        //return (exit_inbuilt(cmd_test[0]));
        exit_inbuilt(&(cmd_test[0]));
        return (1);
    }
   return (0);
}
