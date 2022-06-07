/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbelet <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 09:38:55 by lbelet            #+#    #+#             */
/*   Updated: 2021/10/20 08:27:28 by lbelet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*bloc;

	bloc = malloc(size * count);
	if (!bloc)
		return (NULL);
	ft_memset(bloc, 0, size * count);
	return (bloc);
}
