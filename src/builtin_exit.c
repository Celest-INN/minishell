/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 12:19:17 by ziyang            #+#    #+#             */
/*   Updated: 2026/08/22 18:26:42 by yang             ###   ########.fr       */
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
	if (argv->argc > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		return (exit_free_child(2, pipex));
	}
	if (argv->argc == 2 && !is_number(argv->argv[1]))
	{
		print_error(argv->argv[1]);
		exit_free(pipex, 2);
	}
	if (argv->argc == 2)
		exit_free(pipex, (ft_atoi(argv->argv[1]) % 256 + 256) % 256);
	exit_free(pipex, pipex->env->exit_s);
	return (0);
}
