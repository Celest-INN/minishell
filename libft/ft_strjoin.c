/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erzhuo <erzhuo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 18:12:23 by erzhuo            #+#    #+#             */
/*   Updated: 2025/11/30 19:10:49 by erzhuo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s;
	int		i;
	size_t	len_s1;
	size_t	len_s2;

	if (!s1 || !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	s = (char *)malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (!s)
		return (NULL);
	i = 0;
	ft_memcpy(s, s1, len_s1);
	ft_memcpy(&s[len_s1], s2, len_s2);
	s[len_s1 + len_s2] = '\0';
	return (s);
}
