/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ziyang <ziyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/07 15:20:16 by ziyang            #+#    #+#             */
/*   Updated: 2026/08/07 15:20:19 by ziyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long	ft_abs_digit(long d)
{
	if (d < 0)
		return (-d);
	return (d);
}

static int	len_nbr_long(long nbr)
{
	int	len;

	len = 0;
	if (nbr <= 0)
		len++;
	while (nbr != 0)
	{
		nbr /= 10;
		len++;
	}
	if (nbr == 0 && len == 0)
		len = 1;
	return (len);
}

char	*ft_ltoa(long n)
{
	long	nbr;
	char	*str;
	int		len;

	nbr = n;
	len = len_nbr_long(nbr);
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (nbr == 0)
		str[0] = '0';
	if (nbr < 0)
		str[0] = '-';
	while (nbr != 0)
	{
		len--;
		str[len] = ft_abs_digit(nbr % 10) + '0';
		nbr /= 10;
	}
	return (str);
}
