/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ziyang <ziyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 12:20:26 by ziyang            #+#    #+#             */
/*   Updated: 2026/08/13 18:53:42 by ziyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

char	*file_heredoc_path(char *id)
{
	char	*path;

	if (!id)
		return (NULL);
	path = ft_strjoin("/tmp/.heredoc-", id);
	free(id);
	return (path);
}

int	heredoc_terminated_signal(int fd, char *lim, char *file, t_pipex *pipex)
{
	pid_t	pid;
	int		s;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		free(file);
		signal(SIGINT, heredoc_sighandler);
		if (get_heredoc(fd, lim, pipex->env))
			exit_free(pipex, 1);
		if (g_sig == SIGINT)
			exit_free(pipex, 2);
		exit_free(pipex, 0);
	}
	waitpid(pid, &s, 0);
	return (WEXITSTATUS(s));
}

int	open_heredoc(t_redir *redir, int *stop, t_pipex *pipex)
{
	char	*path;
	int		fd;
	int		r;

	if (*stop != 0 || redir == NULL)
		return (0);
	if (redir->type != HEREDOC)
		return (open_heredoc(redir->next, stop, pipex));
	path = file_heredoc_path(ft_ltoa((int64_t)redir));
	if (!path)
		return (-1);
	fd = open(path, O_WRONLY | O_TRUNC | O_CREAT, 0600);
	if (fd == -1)
		return (free(path), -1);
	r = heredoc_terminated_signal(fd, redir->file, path, pipex);
	(close(fd), free(redir->file), redir->file = path);
	if (r == -1)
		return (free(path), -1);
	if (r == 2)
		return (*stop = 1, r);
	if (r == 1)
		return (1);
	return (open_heredoc(redir->next, stop, pipex));
}

int	all_heredoc(t_argv *cmd, t_pipex *pipex)
{
	int	stop;
	int	r;

	stop = 0;
	if (cmd == NULL)
		return (-1);
	signal(SIGINT, SIG_IGN);
	while (cmd)
	{
		r = open_heredoc(cmd->redir, &stop, pipex);
		if (r != 0)
			return (signal(SIGINT, handle_sigint), r);
		cmd = cmd->next;
	}
	return (signal(SIGINT, handle_sigint), 0);
}

void	unlink_tmp_heredoc(t_argv *cmd)
{
	t_redir	*redir;

	while (cmd != NULL)
	{
		redir = cmd->redir;
		while (redir)
		{
			if (redir->type == HEREDOC && (ft_strncmp(redir->file,
						"/tmp/.heredoc-", 14) == 0) && (access(redir->file,
						F_OK) == 0))
				unlink(redir->file);
			redir = redir->next;
		}
		cmd = cmd->next;
	}
}
