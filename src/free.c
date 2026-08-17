/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ziyang <ziyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 11:53:53 by ziyang            #+#    #+#             */
/*   Updated: 2026/08/09 19:53:34 by ziyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

void	free_pointer(char **s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
}

void	argv_free(t_argv *cmd)
{
	t_redir	*redir;
	t_redir	*tmp;

	if (cmd == NULL)
		return ;
	free_pointer(cmd->argv);
	argv_free(cmd->next);
	redir = cmd->redir;
	while (redir != NULL)
	{
		tmp = redir;
		free(redir->file);
		redir = redir->next;
		free(tmp);
	}
	free(cmd);
}

void	env_free(t_env *env)
{
	free_pointer(env->env);
}

void	exit_free(t_pipex *pipex, int exits)
{
	if (pipex->fd_in != -1)
		close(pipex->fd_in);
	if (pipex->fd_out != -1)
		close(pipex->fd_out);
	argv_free(pipex->argv);
	env_free(pipex->env);
	exit(exits);
}

int	exit_free_child(int exit_s, t_pipex *pipex)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
		exit_free(pipex, exit_s);
	return (pid);
}
