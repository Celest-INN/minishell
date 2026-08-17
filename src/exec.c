/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ziyang <ziyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 11:53:50 by ziyang            #+#    #+#             */
/*   Updated: 2026/08/13 20:04:01 by ziyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_child(t_pipex *pipex, t_argv *cmd)
{
	int	check;

	if (find_binary(pipex->env, cmd->argv) == -1)
		exit_free(pipex, 1);
	if (pipex->fd_in != -1)
	{
		close(STDIN_FILENO);
		if (dup2(pipex->fd_in, STDIN_FILENO) == -1)
			exit_free(pipex, 1);
		close(pipex->fd_in);
	}
	if (pipex->fd_out != -1)
	{
		close(STDOUT_FILENO);
		if (dup2(pipex->fd_out, STDOUT_FILENO) == -1)
			exit_free(pipex, 1);
		close(pipex->fd_out);
	}
	check = path_checker(cmd->argv[0], pipex->env);
	if (check != 0)
		exit_free(pipex, check);
	execve(cmd->argv[0], cmd->argv, pipex->env->env);
	path_cmd_nofound(cmd->argv[0]);
	exit_free(pipex, 126);
}

int	exec_cmds_aux(t_pipex *pipex, t_argv *cmds, int fdpipe[2])
{
	pipex->pid = fork();
	if (pipex->pid == -1)
	{
		close(fdpipe[0]);
		close(fdpipe[1]);
		return (-1);
	}
	if (pipex->pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		close(fdpipe[0]);
		if (open_redir(cmds->redir, pipex))
			exit_free(pipex, 127);
		if (cmds->argc > 0)
			exec_child(pipex, cmds);
		exit_free(pipex, 0);
	}
	return (0);
}

int	exec_cmds(t_pipex *pipex, t_argv *cmds)
{
	int	fdpipe[2];
	int	pid;

	if (pipe(fdpipe) == -1)
		return (-1);
	pipex->fd_out = fdpipe[1];
	pid = exec_built_in(cmds, pipex);
	if (pid == -1)
		return (-1);
	if (pid != 0)
		pipex->pid = pid;
	else
		if (exec_cmds_aux(pipex, cmds, fdpipe) == -1)
			return (-1);
	close(fdpipe[1]);
	pipex->fd_out = -1;
	if (pipex->fd_in != -1)
		close(pipex->fd_in);
	pipex->fd_in = fdpipe[0];
	return (0);
}

int	exec_only_cmd(t_pipex *pipex, t_argv *cmd)
{
	int	r;

	r = exec_built_in(cmd, pipex);
	if (r != 0)
		pipex->pid = r;
	else
	{
		pipex->pid = fork();
		if (pipex->pid == -1)
			return (-1);
		if (pipex->pid == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			if (open_redir(cmd->redir, pipex))
				exit_free(pipex, 1);
			if (cmd->argc > 0)
				exec_child(pipex, cmd);
			exit_free(pipex, 0);
		}
	}
	if (pipex->fd_in != -1)
		close(pipex->fd_in);
	return (0);
}

int	exec(t_argv *cmds, t_pipex *pipex)
{
	int	r;

	r = 0;
	signal(SIGINT, SIG_IGN);
	while (cmds->next != NULL)
	{
		r = 0;
		if (expand_all(cmds, pipex->env))
			return (-1);
		r = exec_cmds(pipex, cmds);
		if (r == -1)
			break ;
		cmds = cmds->next;
	}
	if (expand_all(cmds, pipex->env))
		return (-1);
	r = exec_only_cmd(pipex, cmds);
	wait_child(pipex);
	signal(SIGINT, handle_sigint);
	return (pipex->exit_status);
}
