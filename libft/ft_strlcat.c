/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erzhuo <erzhuo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 18:09:33 by erzhuo            #+#    #+#             */
/*   Updated: 2025/11/30 19:09:23 by erzhuo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// à revoir
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	len_dst;

	if (dstsize == 0)
		return (ft_strlen(src));
	len_dst = ft_strlen(dst);
	if (dstsize < len_dst)
		return (ft_strlen(src) + dstsize);
	i = len_dst;
	j = 0;
	while (i + 1 < dstsize && src[j] != '\0')
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	if (dstsize > len_dst)
		dst[i] = '\0';
	return (ft_strlen(src) + len_dst);
}
