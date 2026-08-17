/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ziyang <ziyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 12:19:22 by ziyang            #+#    #+#             */
/*   Updated: 2026/08/12 14:46:54 by ziyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_identifier_error(char *arg)
{
	ft_putstr_fd("minishell: export: '", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
}

void	print_option_error(char *arg)
{
	ft_putstr_fd("minishell: export: ", STDERR_FILENO);
	if (arg[0] != '\0')
		ft_putchar_fd(arg[0], STDERR_FILENO);
	if (arg[1] != '\0')
		ft_putchar_fd(arg[1], STDERR_FILENO);
	ft_putendl_fd(": invalid option", STDERR_FILENO);
}

int	export_cmp(char *a, char *b)
{
	int	a_len;
	int	b_len;
	int	min_len;
	int	result;

	a_len = var_name_len(a);
	b_len = var_name_len(b);
	min_len = a_len;
	if (b_len < min_len)
		min_len = b_len;
	result = ft_strncmp(a, b, min_len);
	if (result < 0)
		return (1);
	if (result == 0 && a_len < b_len)
		return (1);
	return (0);
}

int	export_args(t_argv *cmd, t_pipex *pipex)
{
	int	i;
	int	s;
	int	append;

	i = 0;
	s = 0;
	while (++i < cmd->argc)
	{
		if (!check_identifier(cmd->argv[i], &append))
		{
			print_identifier_error(cmd->argv[i]);
			s = 1;
			continue ;
		}
		if (append && append_env(pipex->env, cmd->argv[i]))
			return (1);
		if (!append && env_set(pipex->env, cmd->argv[i]))
			return (1);
	}
	return (s);
}

int	builtin_export(t_argv *cmd, t_pipex *pipex)
{
	int	fd;
	int	status;

	if (cmd == NULL || pipex == NULL || pipex->env == NULL)
		return (1);
	fd = pipex->fd_out;
	if (fd == -1)
		fd = STDOUT_FILENO;
	if (cmd->argc == 1)
		status = print_export_list(pipex->env, fd);
	else if (cmd->argv[1][0] == '-')
	{
		print_option_error(cmd->argv[1]);
		status = 2;
	}
	else
		status = export_args(cmd, pipex);
	return (exit_free_child(status, pipex));
}
