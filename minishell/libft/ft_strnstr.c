/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbelet <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 09:14:43 by lbelet            #+#    #+#             */
/*   Updated: 2021/10/20 10:08:52 by lbelet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	s_1;
	size_t	s_2;
	size_t	i;

	i = 0;
	s_1 = ft_strlen(s1);
	s_2 = ft_strlen(s2);
	if (s_2 == 0)
		return ((char *)s1);
	while (i + s_2 <= s_1 && i + s_2 <= n)
	{
		if (!ft_strncmp(s1 + i, s2, s_2))
			return ((char *)(s1 + i));
		i++;
	}
	return (NULL);
}
