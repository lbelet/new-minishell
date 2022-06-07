/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbelet <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 08:27:23 by lbelet            #+#    #+#             */
/*   Updated: 2021/10/20 09:05:46 by lbelet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*d;
	size_t			i;

	i = 0;
	d = dst;
	while (i < n)
	{
		if (d + i == src)
			break ;
		d[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dst);
}
