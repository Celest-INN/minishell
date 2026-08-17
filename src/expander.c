/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erzhuo <erzhuo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 15:05:56 by erzhuo            #+#    #+#             */
/*   Updated: 2026/08/17 17:33:10 by erzhuo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/argv_env.h"

/*
** ~ 展开: ~ 或 ~/xxx -> $HOME/xxx
** HOME 未设置时保持原样 (不再误判为 malloc 失败)
*/
int	expand_home(t_argv *curt, t_env *env)
{
	int		i;
	char	*home;
	char	*tmp;

	i = 0;
	home = find_var("HOME", env);
	if (!home)
		return (1);
	while (curt->argv[i])
	{
		if (curt->argv[i][0] == '~' && (curt->argv[i][1] == 0
				|| curt->argv[i][1] == '/'))
		{
			tmp = ft_strjoin(home, &curt->argv[i][1]);
			if (!tmp)
				return (0);
			free(curt->argv[i]);
			curt->argv[i] = tmp;
		}
		i++;
	}
	return (1);
}

/*
** 单遍从左到右重建字符串: 同时完成 $ 展开和去引号
** i[0]=位置 i[1]=单引号内 i[2]=双引号内
** hd=1 时用于 heredoc 正文: 引号无特殊含义, 原样保留且不阻止展开
** quoted: 出参, 该参数是否出现过起分隔作用的引号
** 关键: 展开出来的内容直接 append, 不再参与后续扫描 -> 不会二次展开
*/
int	expand_str(char **str, t_env *env, int *quoted, int hd)
{
	int		i[3];
	char	*out;

	int_init(i, 3);
	out = ft_strdup("");
	if (!out)
		return (0);
	while ((*str)[i[0]])
	{
		if (!hd && is_quote_char((*str)[i[0]], &i[1], &i[2]))
		{
			*quoted = 1;
			i[0]++;
		}
		else if ((*str)[i[0]] == '$' && !i[1]
			&& is_var_start((*str)[i[0] + 1]))
		{
			if (!append_var(&out, str, i, env))
				return (free(out), 0);
		}
		else if (!append_n(&out, &(*str)[i[0]++], 1))
			return (free(out), 0);
	}
	return (free(*str), *str = out, 1);
}

/*
** heredoc 正文专用入口 (get_heredoc.c 调用)
*/
int	expander_helper(char **str, t_env *env)
{
	int	quoted;

	quoted = 0;
	return (expand_str(str, env, &quoted, 1));
}

/*
** 对一条命令的所有 argv 做展开+去引号
** 展开后为空且从未出现过引号的参数直接删除
** ("$EMPTY" 留空参数, $EMPTY 不留 -> 靠 quoted 区分, 不再依赖执行顺序)
*/
int	expander(t_argv *curt, t_env *env)
{
	int	i;
	int	quoted;

	i = 0;
	while (i < curt->argc)
	{
		quoted = 0;
		if (!expand_str(&(curt->argv[i]), env, &quoted, 0))
			return (0);
		if (curt->argv[i][0] == 0 && !quoted)
		{
			if (rm_empty(curt, i) == 0)
				return (0);
		}
		else
			i++;
	}
	return (1);
}

/*
** expand 总入口
** 1. ~ 展开
** 2. 去掉引号前多余的 $ (如 $"hello" -> "hello")
** 3. argv: 展开 + 去引号 + 删空参数
** 4. 重定向文件名: 展开 + 去引号 (heredoc delimiter 由 get_heredoc 处理)
*/
int	expand_all(t_argv *curt, t_env *env)
{
	if (curt->argc == 0)
	{
		if (!expand_redir(curt, env))
			return (5);
		return (0);
	}
	if (!expand_home(curt, env))
		return (2);
	rm_char(curt);
	if (!expander(curt, env))
		return (3);
	if (!expand_redir(curt, env))
		return (4);
	return (0);
}
