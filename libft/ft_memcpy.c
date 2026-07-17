/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erzhuo <erzhuo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 18:34:34 by erzhuo            #+#    #+#             */
/*   Updated: 2026/07/17 08:41:17 by erzhuo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//size_n est un entier, == unsigned long, int == 32 bits, long == 64 bits
//attention: n est type unsigned long donc il faut que ça ne descende pas au -1
//void * n'est pas void, est un pointeur quelconque
#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	if (!dst && !src)
		return (NULL);
	while (n > 0)
	{
		n--;
		((unsigned char *)dst)[n] = ((unsigned char *)src)[n];
	}
	return (dst);
}

// ((char *)dst)[n] = ((char *)src)[n];
// cast void * en char * avant de modifier 
// car on ne peut pas écrire dans un void * 
// mais ce cast reste locale
// return (dst);
// return un void *