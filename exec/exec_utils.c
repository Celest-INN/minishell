/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ziyang <ziyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 11:54:16 by ziyang            #+#    #+#             */
/*   Updated: 2026/07/18 19:07:03 by ziyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipex_init(t_pipex *pipex, t_argv *cmd, t_env *env)
{
	pipex->env = env;
	pipex->fd_in = -1;
	pipex->fd_out = -1;
	pipex->pid = -1;
	pipex->argv = cmd;
	pipex->exit_status = -1;
}

void	wait_child(t_pipex *pipex)
{
	int	pid;
	int	s;

	pid = wait(&s);
	while (pid != -1)
	{
		if (pid == pipex->pid)
			pipex->exit_status = s;
		pid = wait(&s);
	}
}

void	update_fd(int *oldfd, int newfd)
{
	if (*oldfd != -1)
		close(*oldfd);
	*oldfd = newfd;
}

int	check_redir(t_redir *redir, t_pipex *pipex)
{
	int	tmp;

	if (redir->type == INPUT || redir->type == HEREDOC)
	{
		tmp = open(redir->file, O_RDONLY);
		if (tmp == -1)
			return (-1);
		update_fd(&pipex->fd_in, tmp);
	}
	if (redir->type == OUTPUT)
	{
		tmp = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (tmp == -1)
			return (-1);
		update_fd(&pipex->fd_out, tmp);
	}
	if (redir->type == APPEND)
	{
		tmp = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (tmp == -1)
			return (-1);
		update_fd(&pipex->fd_out, tmp);
	}
	return (0);
}

int	open_redir(t_redir *redir, t_pipex *pipex)
{
	while (redir != NULL)
	{
		if (check_redir(redir, pipex) == -1)
			return (-1);
		redir = redir->next;
	}
	return (0);
}
