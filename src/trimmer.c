/* ************************************************************************** */
/*                                                                            */
/*   trimmer.c                                                                */
/*   作用: 去掉引号, 清理展开后变空的 argv 元素                                */
/*   无改动                                                                    */
/*                                                                            */
/* ************************************************************************** */

#include "argv_env.h"

/*
** 去掉一个字符串中的外层引号
** 跟踪引号状态: 只去掉起分隔作用的引号, 保留被另一种引号保护的
** 例: "it's" -> it's
** 例: 'he said "hi"' -> he said "hi"
*/
void	trim_q(char **s)
{
	int	i;
	int	n;
	int	sq;
	int	dq;

	i = 0;
	n = 0;
	sq = 0;
	dq = 0;
	while ((*s)[i])
	{
		if ((*s)[i] == '\'' && !dq)
			sq = !sq;
		else if ((*s)[i] == '\"' && !sq)
			dq = !dq;
		else
			(*s)[n++] = (*s)[i];
		i++;
	}
	(*s)[n] = 0;
}

void	trim_quote(t_argv *curt)
{
	int	i;

	i = 0;
	while (i < curt->argc)
	{
		trim_q(&(curt->argv[i]));
		i++;
	}
}

/*
** 删除一个空的 argv 元素 (展开后变成空字符串的)
** 返回 -1: 只剩一个且为空, argc 置 0
** 返回 1: 删除成功, 后面的元素前移
** 返回 0: malloc 失败
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

int	trim_empty(t_argv *curt)
{
	int	i;
	int	flag;

	i = 0;
	while (curt->argv[i])
	{
		flag = 10;
		if (curt->argv[i][0] == 0)
		{
			flag = rm_empty(curt, i);
			if (flag == 0)
				return (0);
			if (flag == -1)
				break ;
			if (flag == 1)
				continue ;
		}
		i++;
	}
	return (1);
}
