/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erzhuo <erzhuo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 17:00:58 by erzhuo            #+#    #+#             */
/*   Updated: 2025/11/11 17:15:23 by erzhuo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *b, size_t n)
{
	ft_memset(b, 0, n);
}
//needs to be complied with ft_memset.c
//cc -Wextra -Werror -Wall ft_bzero.c ft_memset.c

// int main(void)
// {
//     char s[] = "hello";
//     write(1, s, 10);
//     write(1, "\n", 1);
//     ft_bzero(s, 3);
//     write(1, s, 10);
// }
