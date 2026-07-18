/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erzhuo <erzhuo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 17:36:54 by erzhuo            #+#    #+#             */
/*   Updated: 2025/11/30 19:12:15 by erzhuo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_in_set(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	int		k;
	char	*result;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	j = ft_strlen(s1) - 1;
	while (s1[i] && is_in_set(s1[i], set))
		i++;
	while (j >= i && is_in_set(s1[j], set))
		j--;
	result = (char *)malloc (sizeof(char) * (j - i + 2));
	if (!result)
		return (NULL);
	k = 0;
	while (k < (j - i + 1))
	{
		result[k] = s1[i + k];
		k++;
	}
	result[k] = '\0';
	return (result);
}
// set 是指针，存储的是地址
// *set 是解引用，获取该地址的值（字符）
// while (*set) 意思是"当前字符不是 '\0'"
//len_s1 = 17;
//i = 6;
//j = 10