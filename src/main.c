/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ziyang <ziyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 11:53:56 by ziyang            #+#    #+#             */
/*   Updated: 2026/08/06 12:21:10 by ziyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_sig = 0;

void	handle_sigint(int sig)
{
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
	g_sig = sig;
}

int	env_init(t_env *env, char *envp[])
{
	size_t	i;

	i = 0;
	while (envp[i])
		i++;
	env->cap = i * 2;
	env->size = i;
	env->env = malloc(sizeof(char *) * env->cap);
	if (env->env == NULL)
		return (-1);
	i = 0;
	while (envp[i])
	{
		env->env[i] = ft_strdup(envp[i]);
		if (env->env[i] == NULL)
		{
			free_pointer(env->env);
			return (-1);
		}
		i++;
	}
	env->env[i] = NULL;
	return (0);
}

void	exec_line(t_env *env, char *line)
{
	t_argv	*cmds;
	t_pipex	pipex;

	if (build_argv(line, env, &cmds) == -1)
		return ;
	pipex_init(&pipex, cmds, env);
	if (all_heredoc(cmds, &pipex) == 0)
		env->exit_s = exec(cmds, &pipex);
	unlink_tmp_heredoc(cmds);
	argv_free(cmds);
}

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_env	env;

	(void)av;
	if (ac != 1)
		return (1);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_sigint);
	if (env_init(&env, envp))
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
		if (g_sig == SIGINT)
			env.exit_s = 130;
	}
	return (env.exit_s);
}

