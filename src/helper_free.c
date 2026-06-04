/* ************************************************************************** */
/*                                                                            */
/*   helper_free.c                                                            */
/*   改动: 新增 free_redir                                                    */
/*   改动: free_argv 中调 free_redir 释放每个节点的重定向链表                  */
/*   去掉: free_entry (wildcard bonus 用的)                                   */
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
