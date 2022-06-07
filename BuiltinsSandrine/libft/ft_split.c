/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbelet <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 09:12:06 by lbelet            #+#    #+#             */
/*   Updated: 2021/10/20 10:18:28 by lbelet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_get_nbr_word(const char *str, char c)
{
	int	nbr;
	int	verif;

	verif = 0;
	nbr = 0;
	while (*str != '\0')                                                                             
	{
		if (*str == c)
		{
			verif = 0;
			str++;
			continue ;
		}
		if (!verif)
		{
			verif = 1;
			nbr++;
		}
		str++;
	}
	return (nbr);
}

void	ft_free_tab(char **tab, int n)
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

void	ft_get_words(char **tab, const char *str, char c, int n)
{
	int	i;
	int	j;

	i = 0;
	while (i < n)
	{
		j = 0;
		while (*str == c)
			str++;
		while (*(str + j) && *(str + j) != c)
			j++;
		tab[i] = ft_substr(str, 0, j);
		if (!tab[i])
		{
			ft_free_tab(tab, i - 1);
			return ;
		}
		str += j;
		i++;
	}
}

char	**ft_split(char const *s, char c)
{
	int		n;
	char	**tab;

	if (!s)
		return (NULL);
	n = ft_get_nbr_word(s, c);
	tab = malloc((n + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	tab[n] = NULL;
	ft_get_words(tab, s, c, n);
	return (tab);
}
