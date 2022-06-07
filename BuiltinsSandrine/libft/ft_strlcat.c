/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbelet <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 09:00:41 by lbelet            #+#    #+#             */
/*   Updated: 2021/10/18 11:45:24 by lbelet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, char *src, size_t size)
{
	size_t	dstlen;
	size_t	srclen;
	size_t	i_dst;
	size_t	i_src;

	dstlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	i_dst = dstlen;
	i_src = 0;
	if (dstlen >= size)
		return (size + srclen);
	while (i_src < srclen && i_dst < (size - 1))
	{
		dst[i_dst] = src[i_src];
		i_dst++;
		i_src++;
	}
	dst[i_dst] = '\0';
	return (dstlen + srclen);
}
