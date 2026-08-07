/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ziyang <ziyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 12:19:41 by ziyang            #+#    #+#             */
/*   Updated: 2026/08/07 14:51:45 by ziyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_exit(t_argv *cmd, t_pipex *pipex)
{
	int	result;

	result = builtin_exit(cmd, pipex);
	if (result)
		return (-2);
	return (0);
}

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
		return (exec_exit(cmd, pipex));
	return (0);
}

int	exec_built_in(t_argv *cmd, t_pipex *pipex)
{
	int	pid;
	int	pid_builtin;
	int	builtin_status;

	if (pipex->argv->next != NULL)
	{
		pid = fork();
		if (pid == -1)
			return (-1);
		if (pid == 0)
		{
			pid_builtin = exec_build_in_child(cmd, pipex);
			waitpid(pid_builtin, &builtin_status, 0);
			exit_free(pipex, WEXITSTATUS(builtin_status));
		}
		return (pid);
	}
	return (exec_build_in_child(cmd, pipex));
}
