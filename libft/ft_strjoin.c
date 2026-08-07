/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erzhuo <erzhuo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 18:12:23 by erzhuo            #+#    #+#             */
/*   Updated: 2026/07/17 08:41:17 by erzhuo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s;

	if (!s1 || !s2)
		return (NULL);
	s = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!s)
		return (NULL);
	ft_memcpy(s, s1, ft_strlen(s1));
	ft_memcpy(&s[ft_strlen(s1)], s2, ft_strlen(s2));
	s[ft_strlen(s1) +ft_strlen(s2)] = '\0';
	return (s);
}
