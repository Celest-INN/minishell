/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trimmer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ziyang <ziyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 09:08:47 by erzhuo            #+#    #+#             */
/*   Updated: 2026/08/07 15:14:31 by ziyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "argv_env.h"

/*
** 去掉一个字符串中起分隔作用的引号 (heredoc delimiter 专用)
** 例: "EOF" -> EOF   'EOF' -> EOF
*/
void	trim_q(char **s)
{
	int	i[3];
	int	n;

	int_init(i, 3);
	n = 0;
	while ((*s)[i[0]])
	{
		if (!is_quote_char((*s)[i[0]], &i[1], &i[2]))
			(*s)[n++] = (*s)[i[0]];
		i[0]++;
	}
	(*s)[n] = 0;
}

/*
** 删除一个空的 argv 元素, 后面的元素前移
** 返回 -1: 只剩一个且为空, argc 置 0
** 返回  1: 删除成功
** 返回  0: malloc 失败
*/
int	rm_empty(t_argv *curt, int i)
{
	char	*tmp;

	if (curt->argc == 1)
	{
		free(curt->argv[0]);
		curt->argv[0] = NULL;
		curt->argc = 0;
		return (-1);
	}
	while (i < curt->argc - 1)
	{
		tmp = ft_strdup(curt->argv[i + 1]);
		if (!tmp)
			return (0);
		free(curt->argv[i]);
		curt->argv[i] = tmp;
		i++;
	}
	free(curt->argv[i]);
	curt->argv[i] = NULL;
	curt->argc--;
	return (1);
}

/*
** 重定向文件名也要展开和去引号: echo hi > $F   cat < "my file"
** heredoc 的 delimiter 不展开, 由 get_heredoc.c 单独处理
*/
int	expand_redir(t_argv *curt, t_env *env)
{
	t_redir	*r;
	int		quoted;

	r = curt->redir;
	while (r)
	{
		quoted = 0;
		if (r->type != HEREDOC && !expand_str(&(r->file), env, &quoted, 0))
			return (0);
		r = r->next;
	}
	return (1);
}
