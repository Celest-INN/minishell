/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erzhuo <erzhuo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 18:29:08 by erzhuo            #+#    #+#             */
/*   Updated: 2025/11/30 18:30:04 by erzhuo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// (converted to an unsigned char) to the string b.
#include "libft.h" //<stdlib.h>

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*s;

	i = 0;
	s = b;
	while (i < len)
	{
		s[i] = c;
		i++;
	}
	return (b);
}
// (*s) c'est un char
//b d'abord c'est une adresse memoire, s = b 
// --> s change le type de void * en char * 
// et s stocke l'adresse memoire qui est stocké dans b
// b et s partage la même mémoire

// int main(void)
// {
//     char s[] = "0123456789";
//     write(1, s, 10);
//     write(1, "\n", 1);
//     ft_memset(s, 'a', 10);
//     write(1, s, 10);
// }