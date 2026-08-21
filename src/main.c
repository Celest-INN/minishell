/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ziyang <ziyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 11:53:56 by ziyang            #+#    #+#             */
/*   Updated: 2026/08/21 19:20:33 by ziyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

int		g_sig = 0;

void	handle_sigint(int sig)
{
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
	g_sig = sig;
}

void	exec_line(t_env *env, char *line)
{
	t_argv	*cmds;
	t_pipex	pipex;
	int		r;

	if (build_argv(line, env, &cmds) == -1)
		return ;
	pipex_init(&pipex, cmds, env);
	r = all_heredoc(cmds, &pipex);
	if (r == 0)
		env->exit_s = exec(cmds, &pipex);
	else
	{
		if (r == 130)
			env->exit_s = 130;
		else if (r >= 0)
			env->exit_s = WEXITSTATUS(r);
		else
			env->exit_s = 1;
	}
	unlink_tmp_heredoc(cmds);
	argv_free(cmds);
}

int	check_tty(void)
{
	if (isatty(STDIN_FILENO) == 0
		|| isatty(STDOUT_FILENO) == 0
		|| isatty(STDERR_FILENO) == 0)
	{
		ft_putstr_fd("minishell: interactive terminal required\n",
			STDERR_FILENO);
		return (-1);
	}
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_env	env;

	(void)av;
	if (ac != 1 || check_tty() == -1)
		return (1);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_sigint);
	if (init_env(&env, envp) == 0)
		return (1);
	line = readline(PROMPT);
	if (g_sig == SIGINT)
		env.exit_s = 130;
	while (line != NULL)
	{
		g_sig = 0;
		add_history(line);
		exec_line(&env, line);
		line = readline(PROMPT);
		if (g_sig)
			env.exit_s = 128 + g_sig;
	}
	env_free(&env);
	return (env.exit_s);
}
