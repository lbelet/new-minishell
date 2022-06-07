#include "minishell.h"

int *ft_code_caractere(char *str)
{
	int *code_caractere;
	int i;
	int dquotes;
    int singlequote;

    code_caractere = malloc((ft_strlen(str) + 1) * sizeof(int));
    i = 0;
    dquotes = 0;
    singlequote = 0;
    while (str[i])
    {
        if (str[i] != 34 && str[i] != 39 && dquotes == 0 && singlequote == 0)
            code_caractere[i] = 6;           
        else if ((str[i] != 34 && str[i] != 39) && (dquotes == 1 || singlequote == 1))
            code_caractere[i] = 7;
        else if ((str[i] == 34 || str[i] == 39) && dquotes == 0 && singlequote == 0)
        {
            if (str[i] == 34)
            {
                code_caractere[i] = 1;
                dquotes = 1;
            }
            if (str[i] == 39)
            {
                code_caractere[i] = 3;
                singlequote = 1;
            }
        }
        else if ((str[i] == 34 && dquotes == 1) || (str[i] == 39 && singlequote == 1))
        {
            if (str[i] == 34)
            {
                code_caractere[i] = 2;
                dquotes = 0;
            }
            if (str[i] == 39)
            {
                code_caractere[i] = 4;
                singlequote = 0;
            }
        }
        else if (str[i] == 34 && singlequote == 1)
            code_caractere[i] = 7;
        else if (str[i] == 39 && dquotes == 1)
            code_caractere[i] = 7;
        i++;
    }
    code_caractere[i] = 0;
    i = 0;
    while (code_caractere[i])
    {
        printf("le code est : %d\n", code_caractere[i]);
        i++;
    }
    
	return (code_caractere);
}