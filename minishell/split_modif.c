#include "minishell.h"

static int	ft_get_nbr_word_modif(const char *str, char c, int *code_caractere, int len)
{
	int	nbr;
	int	verif;
    int i;

	verif = 0;
	nbr = 0;
    i = 0;
	while (*str != '\0')                                                                             
	{
		if (*str == c && code_caractere[len + i] == 6)
		{
			verif = 0;
			str++;
            i++;
			continue ;
		}
		if (!verif)
		{
			verif = 1;
			nbr++;
		}
		str++;
        i++;
	}
	return (nbr);
}

void	ft_free_tab_modif(char **tab, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	ft_get_words_modif(char **tab, const char *str, char c, int n, int *code_caractere, int len)
{
	int	i;
	int	j;
    int k;

	i = 0;
    k = 0;
	while (i < n)
	{
		j = 0;
		while (*str == c && code_caractere[len + k] == 6)
        {
			str++;
            k++;;
        }
		while ((*(str + j) && *(str + j) != c) || (*(str + j) == c && code_caractere[len + k] != 6))
        {
			j++;
			k++;		
        }	
		tab[i] = ft_substr(str, 0, j);
		if (!tab[i])
		{
			ft_free_tab_modif(tab, i - 1);
			return ;
		}
		str += j;
		i++;
	}
}

char	**ft_split_modif(char const *s, char c, int *code_caractere, int len)
{
	int		n;
	char	**tab;

	if (!s)
		return (NULL);
	n = ft_get_nbr_word_modif(s, c, code_caractere, len);
	tab = malloc((n + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	tab[n] = NULL;
	ft_get_words_modif(tab, s, c, n, code_caractere, len);
	return (tab);
}