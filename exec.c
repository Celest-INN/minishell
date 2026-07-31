/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 11:53:50 by ziyang            #+#    #+#             */
/*   Updated: 2026/07/31 20:54:47 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_child(t_pipex *pipex, t_argv *cmd)
{
	int	check;

	if (cmd->redir != NULL)
	{
		if (open_redir(cmd->redir, pipex))
			exit_free(pipex, 1);
	}
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
	check = path_checker(cmd->argv[0]);
	if (check != 0)
		exit_free(pipex, check);
	execve(cmd->argv[0], cmd->argv, pipex->env->env);
}

int	exec_cmds(t_pipex *pipex, t_argv *cmds)
{
	int	fdpipe[2];

	//fonction exec_built-in????
	if (find_binary(pipex->env, cmds->argv) == -1)
		return (-1);
	if (pipe(fdpipe) == -1)
		return (-1);
	pipex->pid = fork();
	if (pipex->pid == -1) 
	{
		(close(fdpipe[0]), close(fdpipe[1]));
		return (-1);
	}
	if (pipex->pid == 0)
	{
		close(fdpipe[0]);
		if (pipex->fd_out != -1)
			close(pipex->fd_out);
		pipex->fd_out = fdpipe[1];
		exec_child(pipex, cmds);
	}
	close(fdpipe[1]);
	if (pipex->fd_in != -1)
		close(pipex->fd_in);
	pipex->fd_in = fdpipe[0];
	return (0);
}

int	exec_only_cmd(t_pipex *pipex, t_argv *cmd)
{
	// built-in??
	if (find_binary(pipex->env, cmd->argv) == -1)
		return (-1);
	pipex->pid = fork();
	if (pipex->pid == -1)
		return (-1);
	if (pipex->pid == 0)
		exec_child(pipex, cmd);
	if (pipex->fd_in != -1)
		close(pipex->fd_in);
	return (0);
}

void	exec(t_argv *cmds, t_env *env, t_pipex	*pipex)
{

	pipex_init(&pipex, cmds, env);
	while (cmds->next != NULL)
	{
		if (exec_cmds(&pipex, cmds) == -1)
			break ;
		cmds = cmds->next;
	}
	exec_only_cmd(&pipex, cmds);
	wait_child(&pipex);
	return (pipex->exit_status);
}
