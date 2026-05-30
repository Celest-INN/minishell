/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erzhuo <erzhuo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 18:30:57 by erzhuo            #+#    #+#             */
/*   Updated: 2025/11/30 18:31:45 by erzhuo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	if (dst == src)
		return (dst);
	i = 0;
	if (dst < src)
	{
		while (i < len)
		{
			((char *)dst)[i] = ((char *)src)[i];
			i++;
		}
		return (dst);
	}
	return (ft_memcpy(dst, src, len));
}
/*
dst et src sont tous les deux un extrait de b 
donc quand on change l'adresse dans la dst 
on change aussi l'adresse dans la src.
cas 1 : quand dst < src, copy à l'endroit
b = hello world
		|     | = src;
	|      |    = dst;

cas 2: quand dst > src, copy à l'envers
b = hello world
	|   |       = src;
	   |      | = dst;

*/