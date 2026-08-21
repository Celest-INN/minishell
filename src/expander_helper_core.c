/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_helper_core.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erzhuo <erzhuo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/20 15:32:40 by erzhuo            #+#    #+#             */
/*   Updated: 2026/08/20 15:38:52 by erzhuo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "argv_env.h"

void	int_init(int *i, int n)
{
	int	x;

	x = 0;
	while (x < n)
	{
		i[x] = 0;
		x++;
	}
}

/*
** 在环境变量中查找变量名, 返回值的指针 (不拷贝)
** 例: find_var("HOME=x", env) -> "/home/user"
*/
char	*find_var(char *str, t_env *env)
{
	int	i;
	int	j;

	j = 0;
	if (!str || !env || !env->env)
		return (NULL);
	while (env->env[j])
	{
		i = 0;
		while (env->env[j][i] && env->env[j][i] != '='
			&& str[i] && env->env[j][i] == str[i])
			i++;
		if (env->env[j][i] == '=' && !is_al(str[i]))
			return (&(env->env[j][i + 1]));
		j++;
	}
	return (NULL);
}

/*
** 把 src 的前 n 个字节追加到 *dst 末尾
*/
int	append_n(char **dst, char *src, int n)
{
	char	*new;
	int		len;
	int		i;

	if (!src || n <= 0)
		return (1);
	len = ft_strlen(*dst);
	new = malloc(sizeof(char) * (len + n + 1));
	if (!new)
		return (0);
	ft_memcpy(new, *dst, len);
	i = 0;
	while (i < n)
	{
		new[len + i] = src[i];
		i++;
	}
	new[len + n] = '\0';
	return (free(*dst), *dst = new, 1);
}

/*
** 展开 (*str)[i[0]] 处的 $VAR 或 $?, 把值追加到 *out
** i[0] 前进到变量名之后
** 变量值是"原样"追加的: 里面的引号和 $ 都不再被解释
*/
int	append_var(char **out, char **str, int *i, t_env *env)
{
	char	*num;
	int		len;

	i[0]++;
	if ((*str)[i[0]] == '?')
	{
		num = ft_itoa(env->exit_s);
		if (!num)
			return (0);
		i[0]++;
		len = append_n(out, num, ft_strlen(num));
		return (free(num), len);
	}
	len = 0;
	while (is_al((*str)[i[0] + len]))
		len++;
	num = find_var(&(*str)[i[0]], env);
	i[0] += len;
	return (append_n(out, num, ft_strlen(num)));
}

/*
** 去掉一个字符串中起分隔作用的引号 (heredoc delimiter 专用)
** 例: "EOF" -> EOF   'EOF' -> EOF
*/
void	trim_q(char *s)
{
	int	i[3];
	int	n;

	int_init(i, 3);
	n = 0;
	while (s[i[0]])
	{
		if (!is_quote_char(s[i[0]], &i[1], &i[2]))
			s[n++] = s[i[0]];
		i[0]++;
	}
	s[n] = 0;
}
