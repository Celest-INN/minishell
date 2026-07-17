/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erzhuo <erzhuo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 17:36:26 by erzhuo            #+#    #+#             */
/*   Updated: 2026/07/17 08:42:51 by erzhuo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_numlen(int n)
{
	int		i;
	long	nb;

	i = 1;
	nb = (long)n;
	if (nb < 0)
	{
		nb *= -1;
		i = 2;
	}
	while (nb > 9)
	{
		nb = nb / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		i;
	long	m;

	i = ft_numlen(n);
	m = (long)n;
	if (m < 0)
		m *= -1;
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (str == NULL)
		return (NULL);
	str[0] = '-';
	str[i] = '\0';
	i--;
	while (m > 9)
	{
		str[i] = m % 10 + '0';
		m = m / 10;
		i--;
	}
	str[i] = m + '0';
	return (&str[0]);
}
// a = len--; a = len
// a = --len; a = len - 1