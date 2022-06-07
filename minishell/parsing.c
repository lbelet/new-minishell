#include "minishell.h"

int ft_subopen_code_caractere(char  *str, int i)
{    
    if (str[i] == 34)
        return (1);
    if (str[i] == 39)
        return (3);
    return (0);
}

int *ft_code_caractere(char *str)
{
	int *code_caractere;
	int i;
    int quotes;

    code_caractere = malloc((ft_strlen(str) + 1) * sizeof(int));
    i = 0;
    quotes = 0;
    while (str[i])
    {
        if (str[i] != 34 && str[i] != 39 && quotes == 0)
            code_caractere[i] = 6;           
        if (((str[i] != 34 && str[i] != 39) && quotes != 0) || 
                (str[i] == 34 && quotes == 3) || (str[i] == 39 && quotes == 1))
            code_caractere[i] = 7;
        if ((str[i] == 34 || str[i] == 39) && quotes == 0)
        {
            quotes = ft_subopen_code_caractere(str, i);
            code_caractere[i] = 1;
        }
        else if ((str[i] == 34 && quotes == 1) || (str[i] == 39 && quotes == 3))
        {
            code_caractere[i] = 2;
            quotes = 0;
        }
        i++;
    }
    code_caractere[i] = 0;
	return (code_caractere);
}

void	ft_check_quote(char **tab, int n)
{
	int code_quote;
	int j;
	int k;
	char temp[50] = {0};

	j = 0;
	code_quote = 0;
	k = 0;
	while (tab[n][j])
	{
        if ((tab[n][j] == 34 || tab[n][j] == 39) && code_quote == 0)
            code_quote = ft_subopen_code_caractere(tab[n], j);
        else if ((tab[n][j] == 34 && code_quote == 1) || (tab[n][j] == 39 && code_quote == 3))
            code_quote = 0;
		else if ((code_quote == 0) || (code_quote == 1 && tab[n][j] != 34) ||
                (code_quote == 3 && tab[n][j] != 39))
			temp[k++] = tab[n][j];
		j++;
	}
	temp[k] = '\0';
	free(tab[n]);
    tab[n] = ft_strdup(temp);
}