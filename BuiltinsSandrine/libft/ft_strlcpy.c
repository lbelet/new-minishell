/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbelet <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 12:24:44 by lbelet            #+#    #+#             */
/*   Updated: 2021/10/20 09:15:55 by lbelet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
	{
		while (src[i])
			i++;
		return (i);
	}
	while (i < size - 1 && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	if (i < size)
		dst[i] = '\0';
	while (src[i])
		i++;
	return (i);
}
//
//int	main(void)
//{
//
//	char	dst[] = "salut";
//	char	src[] = "pepwwf";
//
//	printf ("avant: %s\n", dst);
//	printf ("%lu\n", ft_strlcpy(dst, src, 3));
//	printf ("apres: %s\n", dst);
//	return (0);
//}
