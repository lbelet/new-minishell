/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbelet <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 08:27:34 by lbelet            #+#    #+#             */
/*   Updated: 2021/10/20 09:28:00 by lbelet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned char		*d;
	size_t				i;

	d = (unsigned char *)dst;
	i = 0;
	if (!d && !src)
		return (NULL);
	if (d < (unsigned char *)src)
	{
		while (i < n)
		{
			d[i] = ((unsigned char *)src)[i];
			i++;
		}
	}
	else
	{
		while (n > 0)
		{
			n--;
			d[n] = ((unsigned char *)src)[n];
		}
	}
	return (dst);
}
//
//int	main(void)
//{
//	char	test_s[] = "salut";
//	char	test_d[] = "ab";
//	size_t	len = 3;
//
//	printf("avant: %s\n", test_d);
//	ft_memmove(test_d, test_s, len);
//
//	printf("res: %s\n", test_d);
//	return (0);
//}
