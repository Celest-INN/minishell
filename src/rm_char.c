/* ************************************************************************** */
/*                                                                            */
/*   rm_char.c                                                                */
/*   作用: 处理 $"hello" 和 $'hello' 这种情况                                 */
/*   在引号外遇到 $ 后面紧跟引号时, 去掉 $ 符号                               */
/*   无改动                                                                    */
/*                                                                            */
/* ************************************************************************** */

#include "argv_env.h"

/*
** 跟踪引号状态, 判断当前字符是否是需要展开的 $
** 返回 1: 当前是 $ 且不在单引号内 (需要展开)
** 返回 0: 其他情况
*/
int	check_q(char c, int *q_s, int *q_d)
{
	if (c == '\"' && *q_s == 0)
		*q_d = !(*q_d);
	if (c == '\'' && *q_d == 0)
		*q_s = !(*q_s);
	if (c == '$' && *q_s == 0)
		return (1);
	else
		return (0);
}

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
** 去掉 $"..." 和 $'...' 中多余的 $
** 例: $"hello" -> "hello"
*/
void	rm_char_helper(char **str)
{
	int		i[3];
	int		pos;

	int_init(i, 3);
	while ((*str)[i[0]])
	{
		check_q((*str)[i[0]], &i[1], &i[2]);
		if ((*str)[i[0]] == '$')
		{
			if (!i[1] && !i[2] && (*str)[i[0] + 1]
				&& ((*str)[i[0] + 1] == '\'' || (*str)[i[0] + 1] == '\"'))
			{
				pos = i[0];
				while ((*str)[pos])
				{
					(*str)[pos] = (*str)[pos + 1];
					pos++;
				}
				continue ;
			}
		}
		i[0]++;
	}
}

void	rm_char(t_argv *curt)
{
	int	i;

	i = 0;
	while (i < curt->argc)
	{
		rm_char_helper(&(curt->argv[i]));
		i++;
	}
}
