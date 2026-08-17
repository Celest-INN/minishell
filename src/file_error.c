/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ziyang <ziyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/12 16:30:25 by ziyang            #+#    #+#             */
/*   Updated: 2026/08/13 13:54:45 by ziyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	file_not_found(char *file)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(file, STDERR_FILENO);
	ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
}

void	file_nopermission(char *file)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(file, STDERR_FILENO);
	ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
}

void	file_isdirectory(char *file)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(file, STDERR_FILENO);
	ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
}

void	check_file_error(char *file, int acc)
{
	struct stat	st;

	if (stat(file, &st) == -1)
		return (perror("minishell"));
	if (S_ISDIR(st.st_mode))
		return (file_isdirectory(file));
	if (access(file, F_OK) != 0)
		return (file_not_found(file));
	if (access(file, acc) != 0)
		return (file_nopermission(file));
}
