/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erzhuo <erzhuo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 09:09:32 by erzhuo            #+#    #+#             */
/*   Updated: 2026/07/17 09:09:34 by erzhuo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/argv_env.h"

/*
** 创建一个 token 节点
** WORD: 长度由 token_len 计算
** 双字符操作符 (<< >>): 长度 2
** 单字符操作符 (| < >): 长度 1
*/
t_token	*make_token(char *str, t_token_type type)
{
	t_token	*token;
	int		len;

	if (type == WORD)
		len = token_len(str);
	else if (is_double_op(type))
		len = 2;
	else
		len = 1;
	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = token_strndup(str, len);
	if (!token->value)
		return (free(token), NULL);
	token->next = NULL;
	return (token);
}

/*
** 创建 token 并挂到链表尾部
** 返回值 = 这个 token 在原字符串中占几个字符 (用来推进 i)
*/
int	link_token(t_token **head, t_token **current,
		t_token_type type, char *str)
{
	t_token	*token;

	token = make_token(str, type);
	if (!token)
		return (-1);
	if (!*head)
		*head = token;
	else
		(*current)->next = token;
	*current = token;
	if (is_double_op(type))
		return (2);
	else if (type != WORD)
		return (1);
	return (token_len(str));
}

/*
** 主函数: 逐字符扫描输入, 生成 token 链表
*/
t_token	*lexer(char *line, t_env *env)
{
	int		i;
	int		n;
	t_token	*current;
	t_token	*head;

	current = NULL;
	head = NULL;
	i = 0;
	while (line[i])
	{
		while (line[i] && line[i] <= 32)
			i++;
		if (!line[i])
			break ;
		n = link_token(&head, &current, is_operator(&line[i]), &line[i]);
		if (n < 0)
			return (free_tokens(head), env->exit_s = 1, NULL);
		i += n;
	}
	return (head);
}
