/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ziyang <ziyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 11:53:37 by ziyang            #+#    #+#             */
/*   Updated: 2026/08/13 19:18:02 by ziyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	only_cd(t_env *env)
{
	char	*home;

	home = get_env_value(env, "HOME");
	if (home == NULL)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
		return (-1);
	}
	return (update_directory(home, env));
}

int	cd_directory(char *name)
{
	struct stat	st;
	char		*tmp;

	if (stat(name, &st) == -1)
	{
		tmp = ft_strjoin("minishell: cd: ", name);
		perror(tmp);
		free(tmp);
		return (-1);
	}
	if (!S_ISDIR(st.st_mode))
	{
		tmp = ft_strjoin("minishell: cd: ", name);
		ft_putstr_fd(tmp, STDERR_FILENO);
		ft_putstr_fd(": Not a directory\n", STDERR_FILENO);
		free(tmp);
		return (-1);
	}
	return (0);
}

int	update_directory(char *dir, t_env *env)
{
	char	*tmp;

	if (dir == NULL)
		return (0);
	tmp = ft_strdup(dir);
	if (tmp == NULL)
		return (-1);
	if (update_oldpwd(env) == -1)
		return (free(tmp), -1);
	if (chdir(tmp))
	{
		free(tmp);
		perror("chdir");
		return (-1);
	}
	free(tmp);
	if (update_pwd(env))
		return (-1);
	return (0);
}

int	builtin_cd(t_argv *cmd, t_pipex *pipex)
{
	if (cmd->argc > 2)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", STDERR_FILENO);
		return (exit_free_child(2, pipex));
	}
	if (cmd->argc == 1)
	{
		if (only_cd(pipex->env) == -1)
			return (exit_free_child(1, pipex));
		return (exit_free_child(0, pipex));
	}
	if (cd_directory(cmd->argv[1]) == -1)
		return (exit_free_child(1, pipex));
	if (update_directory(cmd->argv[1], pipex->env) == -1)
		return (exit_free_child(1, pipex));
	return (exit_free_child(0, pipex));
}
