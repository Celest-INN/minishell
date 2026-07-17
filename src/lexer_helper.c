/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erzhuo <erzhuo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 09:09:20 by erzhuo            #+#    #+#             */
/*   Updated: 2026/07/17 09:09:22 by erzhuo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "argv_env.h"

/*
** 判断当前字符是否是操作符, 返回对应的 token 类型
** 双字符操作符 (<< >>) 必须在单字符 (< >) 前面判断
*/
int	is_operator(char *str)
{
	if (*str == '|')
		return (PIPE);
	else if (*str == '<' && *(str + 1) == '<')
		return (HEREDOC);
	else if (*str == '>' && *(str + 1) == '>')
		return (APPEND);
	else if (*str == '<')
		return (INPUT);
	else if (*str == '>')
		return (OUTPUT);
	return (WORD);
}

/* 是否是重定向操作符 */
int	is_redir_type(t_token_type type)
{
	return (type == INPUT || type == OUTPUT
		|| type == APPEND || type == HEREDOC);
}

/* 是否是双字符操作符 (<< 或 >>) */
int	is_double_op(t_token_type type)
{
	return (type == HEREDOC || type == APPEND);
}

/*
** 计算一个 WORD token 的长度
** 遇到空白或操作符就停
** 引号内的内容 (包括空格) 不会打断 token
*/
int	token_len(char *str)
{
	int		x;
	char	q;

	x = 0;
	if (!str)
		return (0);
	while (str[x])
	{
		if (str[x] == '\'' || str[x] == '\"')
		{
			q = str[x++];
			while (str[x] && str[x] != q)
				x++;
			if (str[x] == q)
				x++;
		}
		else if (str[x] <= 32 || is_operator(&str[x]) != WORD)
			break ;
		else
			x++;
	}
	return (x);
}

char	*token_strndup(const char *s, int n)
{
	char	*dup;
	int		i;

	if (n <= 0)
		return (NULL);
	i = 0;
	dup = (char *)malloc(sizeof(char) * (n + 1));
	if (!dup)
		return (NULL);
	while (i < n)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
