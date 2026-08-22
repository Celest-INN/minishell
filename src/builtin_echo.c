/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 16:45:20 by ziyang            #+#    #+#             */
/*   Updated: 2026/08/22 16:46:40 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo_n(char *s)
{
	int	i;

	if (s == NULL || s[0] != '-')
		return (0);
	i = 1;
	while (s[i] == 'n')
		i++;
	if (i > 1 && s[i] == '\0')
		return (1);
	return (0);
}

void	echo_args(int ac, char **av, int s, int fd)
{
	while (s < ac)
	{
		ft_putstr_fd(av[s], fd);
		if (s < ac - 1)
			ft_putstr_fd(" ", fd);
		s++;
	}
}

int	builtin_echo(t_argv *cmd, t_pipex *pipex)
{
	int	add_newline;
	int	start;
	int	fd_out;

	if (cmd == NULL || pipex == NULL)
		return (exit_free_child(1, pipex));
	fd_out = pipex->fd_out;
	if (fd_out == -1)
		fd_out = STDOUT_FILENO;
	add_newline = 1;
	start = 1;
	while (start < cmd->argc && echo_n(cmd->argv[start]))
	{
		add_newline = 0;
		start++;
	}
	echo_args(cmd->argc, cmd->argv, start, fd_out);
	if (add_newline)
		ft_putstr_fd("\n", fd_out);
	pipex->exit_status = 0;
	return (exit_free_child(0, pipex));
}
