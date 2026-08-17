/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erzhuo <erzhuo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 18:03:22 by erzhuo            #+#    #+#             */
/*   Updated: 2025/11/30 19:15:28 by erzhuo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*result;
	unsigned int	i;
	size_t			len_s;

	if (!s || !f)
		return (NULL);
	i = 0;
	len_s = ft_strlen(s);
	result = (char *)malloc(sizeof(char) * (len_s + 1));
	if (!result)
		return (NULL);
	while (s[i])
	{
		result[i] = f(i, s[i]);
		i++;
	}
	result[i] = '\0';
	return (result);
}
// *f est un pointeur de fonction 
// les fonctions sont dans la memoire 
// *f prend l'addresse de la fonction dans la memoire