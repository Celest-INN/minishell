/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erzhuo <erzhuo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 09:08:59 by erzhuo            #+#    #+#             */
/*   Updated: 2026/07/17 09:09:02 by erzhuo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "argv_env.h"

void	free_strstr(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		free(s[i++]);
	free(s);
}

void	free_env(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->size)
	{
		if (env->env[i])
			free(env->env[i]);
		i++;
	}
	if (env->env)
		free(env->env);
}

void	free_tokens(t_token *head)
{
	t_token	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		if (tmp->value)
			free(tmp->value);
		free(tmp);
	}
}

/* 新增: 释放重定向链表 */
void	free_redir(t_redir *head)
{
	t_redir	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		if (tmp->file)
			free(tmp->file);
		free(tmp);
	}
}

/* 改动: 每个节点额外释放 redir 链表 */
void	free_argv(t_argv *head)
{
	t_argv	*tmp;
	int		i;

	while (head)
	{
		i = 0;
		tmp = head;
		head = head->next;
		if (tmp->argv)
		{
			while (i < tmp->argc)
			{
				if (tmp->argv[i])
					free(tmp->argv[i]);
				i++;
			}
			free(tmp->argv);
		}
		free_redir(tmp->redir);
		free(tmp);
	}
}
