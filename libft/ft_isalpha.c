/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erzhuo <erzhuo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 17:02:44 by erzhuo            #+#    #+#             */
/*   Updated: 2025/11/30 18:42:23 by erzhuo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}
/*
#include <stdio.h>

int main(void)
{
	printf("%d", ft_isalpha('a'));
	printf("%d", ft_isalpha('Z'));
	printf("%d", ft_isalpha('1'));
}
*/
