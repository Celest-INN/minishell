/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_helper_is.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erzhuo <erzhuo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/20 15:21:06 by erzhuo            #+#    #+#             */
/*   Updated: 2026/08/20 15:39:07 by erzhuo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "argv_env.h"

int	is_al(char c)
{
	if (c == '_')
		return (1);
	else if (c >= 'a' && c <= 'z')
		return (1);
	else if (c >= 'A' && c <= 'Z')
		return (1);
	else if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

/*
** $ 后面跟着这个字符才算变量展开, 否则 $ 原样输出
*/
int	is_var_start(char c)
{
	return (c == '?' || is_al(c));
}

/*
** 判断当前字符是否是"起分隔作用"的引号, 是则翻转状态并返回 1
** 被另一种引号保护的引号返回 0 (原样保留)
*/
int	is_quote_char(char c, int *sq, int *dq)
{
	if (c == '\'' && *dq == 0)
	{
		*sq = !(*sq);
		return (1);
	}
	if (c == '\"' && *sq == 0)
	{
		*dq = !(*dq);
		return (1);
	}
	return (0);
}
