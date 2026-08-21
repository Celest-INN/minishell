/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erzhuo <erzhuo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 09:10:19 by erzhuo            #+#    #+#             */
/*   Updated: 2026/08/21 19:00:14 by erzhuo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/argv_env.h"

/*
** 预检查: 引号是否闭合 (不再检查括号)
*/
int	precheck_line(char *line)
{
	int	single_q;
	int	double_q;

	single_q = 0;
	double_q = 0;
	while (*line)
	{
		if (*line == '\'' && double_q == 0)
			single_q = !single_q;
		else if (*line == '\"' && single_q == 0)
			double_q = !double_q;
		line++;
	}
	if (single_q || double_q)
		return (1);
	return (0);
}

/*
** 返回: 1 = pipe, 2 = redir, 0 = word
*/
int	is_op(t_token_type x)
{
	if (x == PIPE)
		return (1);
	else if (is_redir_type(x))
		return (2);
	return (0);
}

/*
** 语法检查: 返回出错的 token 值, 没错返回 NULL
** 规则:
**   - 不能以 pipe 开头
**   - 不能以操作符结尾
**   - pipe 后面不能跟 pipe
**   - redir 后面必须跟 word (文件名)
*/
char	*syntax_check(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	if (tmp->type == PIPE)
		return (tmp->value);
	while (tmp)
	{
		if (!tmp->next && is_op(tmp->type) > 0)
			return ("newline");
		if (tmp->next)
		{
			if (is_op(tmp->type) == 1 && is_op(tmp->next->type) == 1)
				return (tmp->next->value);
			if (is_op(tmp->type) == 2 && is_op(tmp->next->type) > 0)
				return (tmp->next->value);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

int	syntax_error(char *line, t_token *token, t_env *env)
{
	char	*x;

	if (precheck_line(line) != 0)
	{
		env->exit_s = 2;
		write(2, "syntax error: unclosed quote\n", 29);
		return (1);
	}
	x = syntax_check(token);
	if (x != NULL)
	{
		env->exit_s = 2;
		write(2, "syntax error near unexpected token `", 36);
		write(2, x, ft_strlen(x));
		write(2, "'\n", 2);
		return (2);
	}
	return (0);
}
