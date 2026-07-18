/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erzhuo <erzhuo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 18:40:07 by erzhuo            #+#    #+#             */
/*   Updated: 2025/11/30 18:40:09 by erzhuo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//*s n'est pas forcément un string
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char *)s)[i] == (unsigned char)c)
			return ((void *)&s[i]);
		i++;
	}
	return (NULL);
}

// return ((void *)&s[i]);
// on peut aussi écrire: return (char *)str+i
// str c'est l'adresse du premier caratère du string!!!!!! 
// +i ça donne l'adresse du str[i] et ça return le string à partir de str[i]