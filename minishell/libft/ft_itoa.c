/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbelet <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 08:26:34 by lbelet            #+#    #+#             */
/*   Updated: 2021/10/20 12:31:46 by lbelet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_intlen(int n)
{
	size_t			i;
	unsigned int	k;

	i = 0;
	if (n == 0)
		i++;
	if (n < 0)
	{
		i++;
		k = (unsigned int)(n * -1);
	}
	else
		k = (unsigned int)n;
	while (k > 0)
	{
		k = k - (k % 10);
		k = k / 10;
		i++;
	}
	return (i);
}

static unsigned int	ft_check_neg(int n)
{
	unsigned int	k;

	if (n < 0)
		k = (unsigned int)(n * -1);
	else
		k = (unsigned int)n;
	return (k);
}

char	*ft_itoa(int n)
{	
	size_t			len;
	unsigned int	k;
	char			*res;

	k = ft_check_neg(n);
	len = ft_intlen(n);
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	if (n < 0)
		res[0] = '-';
	res[len] = '\0';
	if (k == 0)
		res[len - 1] = 0 + '0';
	while (k > 0)
	{
		res[len - 1] = k % 10 + '0';
		k = k - (k % 10);
		k = k / 10;
		len--;
	}
	return (res);
}
//int	main(void)
//{
//	int	test;
//	char	*res;
//	int	controle;
//
//	test = -1234;
//	controle = ft_intlen(test);
//	res = ft_itoa(test);
//	printf ("ft_intlen: %d\n", controle);
//	printf ("ft_itoa: %s\n", res);
//	return (0);
//
//}	
