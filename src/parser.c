/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erzhuo <erzhuo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 09:09:53 by erzhuo            #+#    #+#             */
/*   Updated: 2026/08/22 19:05:57 by erzhuo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/argv_env.h"

/*
** 解析一条命令 (从当前位置到 PIPE 或链表结束)
** 1. 数 argv 参数个数
** 2. 提取重定向到 t_redir 链表
** 3. 提取 WORD 到 argv 数组
** 4. 推进 token 指针到 PIPE 之后 (下一条命令的起点)
*/
t_argv	*parse_command(t_token **token)
{
	t_argv	*node;
	t_token	*start;

	start = *token;
	node = malloc(sizeof(t_argv));
	if (!node)
		return (NULL);
	node->next = NULL;
	node->argv = NULL;
	node->redir = NULL;
	node->argc = count_cmd_argc(start);
	if (build_redirs(start, &node->redir) < 0)
		return (free_argv(node), NULL);
	if (build_argv_arr(node, start) < 0)
		return (free_argv(node), NULL);
	while (*token && (*token)->type != PIPE)
		*token = (*token)->next;
	if (*token && (*token)->type == PIPE)
		*token = (*token)->next;
	return (node);
}

/*
** 主循环: 逐条解析命令, 用 next 串起来
*/
t_argv	*make_argv(t_token *token)
{
	t_argv	*head;
	t_argv	*current;
	t_argv	*new;

	head = NULL;
	current = NULL;
	while (token)
	{
		new = parse_command(&token);
		if (!new)
			return (free_argv(head), NULL);
		if (!head)
			head = new;
		else
			current->next = new;
		current = new;
	}
	return (head);
}

/*
** 入口函数: lexer -> syntax check -> parser
*/
int	build_argv(char *line, t_env *env, t_argv **out)
{
	t_token	*token;
	t_argv	*head;

	*out = NULL;
	if (!line[0])
		return (free(line), env->exit_s = 0, -1);
	token = lexer(line, env);
	if (!token)
		return (free(line), -1);
	if (syntax_error(line, token, env))
		return (free_tokens(token), free(line), -1);
	head = make_argv(token);
	if (!head)
		return (free_tokens(token), free_env(env),
			free(line), exit(1), 0);
	*out = head;
	free_tokens(token);
	free(line);
	return (1);
}
