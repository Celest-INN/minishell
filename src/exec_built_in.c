/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 12:19:41 by ziyang            #+#    #+#             */
/*   Updated: 2026/08/22 16:43:54 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_build_in_child(t_argv *cmd, t_pipex *pipex)
{
	if (!ft_strcmp(cmd->argv[0], "cd"))
		return (builtin_cd(cmd, pipex));
	if (!ft_strcmp(cmd->argv[0], "pwd"))
		return (builtin_pwd(pipex));
	if (!ft_strcmp(cmd->argv[0], "echo"))
		return (builtin_echo(cmd, pipex));
	if (!ft_strcmp(cmd->argv[0], "export"))
		return (builtin_export(cmd, pipex));
	if (!ft_strcmp(cmd->argv[0], "unset"))
		return (builtin_unset(cmd, pipex));
	if (!ft_strcmp(cmd->argv[0], "env"))
		return (builtin_env(cmd, pipex));
	if (!ft_strcmp(cmd->argv[0], "exit"))
		return (builtin_exit(cmd, pipex));
	return (0);
}

int	is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "cd"))
		return (1);
	if (!ft_strcmp(cmd, "pwd"))
		return (1);
	if (!ft_strcmp(cmd, "echo"))
		return (1);
	if (!ft_strcmp(cmd, "export"))
		return (1);
	if (!ft_strcmp(cmd, "unset"))
		return (1);
	if (!ft_strcmp(cmd, "env"))
		return (1);
	if (!ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

int	exec_built_in(t_argv *cmd, t_pipex *pipex)
{
	int	pid;
	int	pid_builtin;
	int	builtin_status;

	if (cmd->argc == 0 || is_builtin(cmd->argv[0]) == 0)
		return (0);
	if (open_redir(cmd->redir, pipex))
		return (exit_free_child(1, pipex));
	if (pipex->argv->next != NULL)
	{
		pid = fork();
		if (pid == -1)
			return (-1);
		if (pid == 0)
		{
			signal(SIGINT, SIG_DFL);
			pid_builtin = exec_build_in_child(cmd, pipex);
			waitpid(pid_builtin, &builtin_status, 0);
			exit_free(pipex, WEXITSTATUS(builtin_status));
		}
		return (close_fd(pipex->fd_in), close_fd(pipex->fd_out), pid);
	}
	pid = exec_build_in_child(cmd, pipex);
	(close_fd(pipex->fd_in), close_fd(pipex->fd_out));
	return (pid);
}
