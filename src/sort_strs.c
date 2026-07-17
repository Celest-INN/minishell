/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_strs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erzhuo <erzhuo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 09:10:09 by erzhuo            #+#    #+#             */
/*   Updated: 2026/07/17 09:10:12 by erzhuo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "argv_env.h"

// void	*ft_memcpy(void *dest, const void *src, size_t n)
// {
// 	unsigned char	*tmp_d;
// 	unsigned char	*tmp_s;

// 	if (dest == NULL && src == NULL)
// 		return (NULL);
// 	tmp_d = (unsigned char *)dest;
// 	tmp_s = (unsigned char *)src;
// 	while (n > 0)
// 	{
// 		*tmp_d = *tmp_s;
// 		tmp_d++;
// 		tmp_s++;
// 		n--;
// 	}
// 	return (dest);
// }

// char	*ft_strjoin(char const *s1, char const *s2)
// {
// 	char	*join;

// 	join = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
// 	if (join == 0)
// 		return (NULL);
// 	ft_memcpy(join, s1, ft_strlen(s1));
// 	ft_memcpy(&join[ft_strlen(s1)], s2, ft_strlen(s2));
// 	join[ft_strlen(s1) + ft_strlen(s2)] = 0;
// 	return (join);
// }
