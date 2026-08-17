/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ziyang <ziyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 11:54:07 by ziyang            #+#    #+#             */
/*   Updated: 2026/08/13 20:07:50 by ziyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	path_nopermission_execute(char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": Permission denied\n", 2);
	return (126);
}

int	path_cmd_nofound(char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": Command not found\n", 2);
	return (127);
}

int	path_isdirectory(char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": Is a directory\n", 2);
	return (126);
}

int	is_path(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

int	path_checker(char *path, t_env *env)
{
	struct stat	st;
	char		*env_path;

	env_path = get_env_value(env, "PATH");
	if (is_path(path) == 0 && (env_path != NULL && env_path[0] != '\0'))
		return (path_cmd_nofound(path));
	if ((path[0] == '.' && path[1] == '\0')
		|| (path[0] == '.' && path[1] == '.' && path[2] == '\0')
		|| access(path, F_OK) != 0)
		return (path_cmd_nofound(path));
	if (access(path, X_OK) != 0)
		return (path_nopermission_execute(path));
	stat(path, &st);
	if (S_ISDIR(st.st_mode))
		return (path_isdirectory(path));
	return (0);
}
