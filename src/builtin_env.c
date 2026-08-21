/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ziyang <ziyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 12:18:57 by ziyang            #+#    #+#             */
/*   Updated: 2026/08/13 17:38:00 by ziyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_auxiliary(t_argv *cmd, t_pipex *pipex)
{
	int	i;

	if (cmd->argc > 1)
	{
		ft_putendl_fd("minishell: env: too many arguments", STDERR_FILENO);
		exit_free(pipex, 127);
	}
	i = 0;
	while (i < pipex->env->size)
	{
		if (var_name_len(pipex->env->env[i])
			== (int)ft_strlen(pipex->env->env[i]))
		{
			i++;
			continue ;
		}
		if (pipex->fd_out == -1)
			ft_putendl_fd(pipex->env->env[i], STDOUT_FILENO);
		else
			ft_putendl_fd(pipex->env->env[i], pipex->fd_out);
		i++;
	}
	exit_free(pipex, 0);
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
