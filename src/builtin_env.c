/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ziyang <ziyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 12:18:57 by ziyang            #+#    #+#             */
/*   Updated: 2026/08/07 15:13:01 by ziyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_env_process(t_pipex *pipex)
{
	if (pipex->fd_in > 2)
		close(pipex->fd_in);
	if (pipex->fd_out > 2)
		close(pipex->fd_out);
	argv_free(pipex->argv);
	env_free(pipex->env);
}

int	env_auxiliary(t_argv *cmd, t_pipex *pipex)
{
	int	i;

	if (cmd->argc > 1)
	{
		ft_putendl_fd("minishell: env: too many arguments", STDERR_FILENO);
		clean_env_process(pipex);
		exit(127);
	}
	i = 0;
	while (i < pipex->env->size)
	{
		if (pipex->fd_out == -1)
			ft_putendl_fd(pipex->env->env[i], STDOUT_FILENO);
		else
			ft_putendl_fd(pipex->env->env[i], pipex->fd_out);
		i++;
	}
	clean_env_process(pipex);
	exit(0);
}

int	builtin_env(t_argv *cmd, t_pipex *pipex)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (!pid)
		env_auxiliary(cmd, pipex);
	return (pid);
}
