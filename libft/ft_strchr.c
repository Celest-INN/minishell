/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erzhuo <erzhuo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 17:35:28 by erzhuo            #+#    #+#             */
/*   Updated: 2025/11/30 18:17:44 by erzhuo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// characters are just labels for byte values
// on peut aussi écrire: return (char *)str+i
// str c'est l'adresse du premier caratère du string! 
// +i ça donne l'adresse du str[i] et ça return le string à partir de str[i]
// car quand str[i] == '\0', ça rentre plus dans la boucle while
// donc ça va pas return l'adresse du '\0'

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if ((unsigned char)s[i] == (unsigned char)c)
			return ((char *)&s[i]);
		i++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)&s[i]);
	return (NULL);
}

//&s[strlen(s)]
// #include <stdio.h>
// int main(){
// 	char s[] = "teste";
// 	printf("%p %p\n", s, ft_strchr(s, '\0'));
// }