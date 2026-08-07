/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ziyang <ziyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 12:19:17 by ziyang            #+#    #+#             */
/*   Updated: 2026/08/07 14:51:14 by ziyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_number(char *arg)
{
	if (arg[0] == '\0')
		return (0);
	if (arg[0] == '-' || arg[0] == '+')
		++arg;
	while ('0' <= *arg && *arg <= '9')
		++arg;
	return (*arg == '\0');
}

static void	print_error(char *arg)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
}

int	builtin_exit(t_argv *argv, t_pipex *pipex)
{
	if (pipex->fd_in != -1 && pipex->fd_in != STDIN_FILENO)
		close(pipex->fd_in);
	if (pipex->fd_out != -1 && pipex->fd_out != STDOUT_FILENO)
		close(pipex->fd_out);
	if (argv->argc > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		return (0);
	}
	if (argv->argc == 2 && !is_number(argv->argv[1]))
	{
		print_error(argv->argv[1]);
		exit_free(pipex, 2);
	}
	if (argv->argc == 2)
		exit_free(pipex, (ft_atoi(argv->argv[1]) % 256 + 256) % 256);
	return (0);
}
