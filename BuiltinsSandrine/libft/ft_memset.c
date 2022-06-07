/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbelet <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 08:27:45 by lbelet            #+#    #+#             */
/*   Updated: 2021/10/18 08:28:06 by lbelet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int i, size_t len)
{
	char	*str;

	str = s;
	while (len)
	{
		*str = (unsigned char)i;
		str++;
		len--;
	}
	return (s);
}

//int	main(void)
//{
//	char test[50] = "salut les ploucs de 42";
//	printf("\nAvant ft_memset(): %s\n", test);
//	ft_memset(test + 4, '.', 6*sizeof(char));
//	printf("Apres ft_memset(): %s", test);
//	return (0);
//}
