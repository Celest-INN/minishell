/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ziyang <ziyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 11:54:07 by ziyang            #+#    #+#             */
/*   Updated: 2026/07/18 12:47:43 by ziyang           ###   ########.fr       */
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
	ft_putstr_fd(": 'Command not found\n", 2);
	return (127);
}

int	path_checker(char *path)
{
	if (access(path, F_OK) != 0)
		return (path_cmd_nofound);
	if (access(path, X_OK) != 0)
		return (path_nopermission_execute(path));
	return (0);
}
