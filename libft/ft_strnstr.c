/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erzhuo <erzhuo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 17:38:09 by erzhuo            #+#    #+#             */
/*   Updated: 2025/11/30 19:02:28 by erzhuo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	if (needle[0] == '\0')
		return ((char *)haystack);
	j = 0;
	i = 0;
	while (j < len && needle[i] && haystack[j])
	{
		i = 0;
		while (needle[i] && needle[i] == haystack[j + i] && j + i < len)
			i++;
		if (needle[i] == '\0')
			return ((char *)&haystack[j]);
		j++;
	}
	return (NULL);
}
// char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
// {
//	 size_t  i;
//	 size_t  j;
//	 size_t  k;

//	 if (!needle)
//		 return ((char *)haystack);
//	 j = 0;
//	 while (haystack[j] && j < len)
//	 {
//		 i = 0;
//		 k = j;
//		 while (needle[i] == haystack[k] && k < len)
//		 {
//			 i++;
//			 k++;
//		 }
//		 // comment tu sais que t'as trouvé needle??
//		 if (needle[i] == '\0')
//			 return ((char *)&haystack[j]);
//		 j++; 
//	 }
//	 return (NULL);
// }

// needle = hello
// haystack = hellx world
// len = 4
// ==> null
