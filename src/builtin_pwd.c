/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ziyang <ziyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 12:19:25 by ziyang            #+#    #+#             */
/*   Updated: 2026/08/07 15:12:51 by ziyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd(t_pipex *pipex)
{
	char	*cwd;

	cwd = get_cwd();
	if (cwd == NULL)
		return (exit_free_child(1, pipex));
	if (pipex->fd_out == -1)
		ft_putendl_fd(cwd, STDOUT_FILENO);
	else
		ft_putendl_fd(cwd, pipex->fd_out);
	free(cwd);
	return (exit_free_child(0, pipex));
}
