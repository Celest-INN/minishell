/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ziyang <ziyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 12:19:28 by ziyang            #+#    #+#             */
/*   Updated: 2026/08/10 16:48:25 by ziyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_option(char *arg)
{
	ft_putstr_fd("minishell: unset: ", STDERR_FILENO);
	if (arg[0] != '\0')
		ft_putchar_fd(arg[0], STDERR_FILENO);
	if (arg[1] != '\0')
		ft_putchar_fd(arg[1], STDERR_FILENO);
	ft_putendl_fd(": invalid option", STDERR_FILENO);
}

void	remove_env_var(t_env *env, int index)
{
	int	i;

	if (env == NULL || index < 0 || index >= env->size)
		return ;
	free(env->env[index]);
	i = index;
	while (i < env->size - 1)
	{
		env->env[i] = env->env[i + 1];
		i++;
	}
	env->size--;
	env->env[env->size] = NULL;
}

int	builtin_unset(t_argv *cmd, t_pipex *pipex)
{
	int	i;
	int	index;

	if (cmd == NULL || pipex == NULL || pipex->env == NULL)
		return (1);
	if (cmd->argc == 1)
		return (exit_free_child(0, pipex));
	if (cmd->argv[1][0] == '-')
	{
		unset_option(cmd->argv[1]);
		return (exit_free_child(2, pipex));
	}
	i = 0;
	while (++i < cmd->argc)
	{
		index = env_var_index(pipex->env, cmd->argv[i],
				ft_strlen(cmd->argv[i]));
		if (index != pipex->env->size)
			remove_env_var(pipex->env, index);
	}
	return (exit_free_child(0, pipex));
}
