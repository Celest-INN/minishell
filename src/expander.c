/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ziyang <ziyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 09:08:47 by erzhuo            #+#    #+#             */
/*   Updated: 2026/08/07 15:14:31 by ziyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/argv_env.h"

/*
** ~ 展开: ~/xxx -> /home/user/xxx
*/
int	expand_home(t_argv *curt, t_env *env)
{
	int		i;
	char	*home;
	char	*tmp;

	i = 0;
	home = find_var("HOME", env);
	while (curt->argv[i])
	{
		if ((curt->argv[i][0] == '~' && curt->argv[i][1] == 0)
			|| (curt->argv[i][0] == '~' && curt->argv[i][1] == '/'))
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
** 对一个字符串做 $VAR 展开
** 跟踪引号状态: 单引号内不展开, 双引号内展开
** $? 展开为上一条命令的退出码
*/
int	expander_helper(char **str, t_env *env)
{
	int		i[3];
	char	*var;

	int_init(i, 3);
	while ((*str)[i[0]])
	{
		if (check_q((*str)[i[0]], &i[1], &i[2]))
		{
			if ((*str)[++i[0]] == 0)
				break ;
			if ((*str)[i[0]] == '?')
				var = NULL;
			else if (!is_al((*str)[i[0]]))
				continue ;
			else
				var = find_var(&(*str)[i[0]], env);
			if (!replace_var(str, var, i[0], env))
				return (0);
			i[0] -= 2;
		}
		i[0]++;
	}
	return (1);
}

/*
** 对一条命令的所有 argv 做 $VAR 展开
*/
int	expander(t_argv *curt, t_env *env)
{
	int	i;

	i = 0;
	while (i < curt->argc)
	{
		if (!expander_helper(&(curt->argv[i]), env))
			return (0);
		i++;
	}
	return (1);
}

/*
** expand 总入口: 对一条命令做所有展开
** 1. ~ 展开
** 2. 去掉引号前的 $ (如 $"hello" -> "hello")
** 3. $VAR 展开
** 4. 去掉展开后变成空的 argv
** 5. 去掉引号
*/
int	expand_all(t_argv *curt, t_env *env)
{
	if (curt->argc == 0)
		return (0);
	if (!expand_home(curt, env))
		return (2);
	rm_char(curt);
	if (!expander(curt, env))
		return (3);
	if (!trim_empty(curt))
		return (4);
	trim_quote(curt);
	return (0);
}
