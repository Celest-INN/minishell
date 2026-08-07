/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester_ec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erzhuo <erzhuo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 09:10:29 by erzhuo            #+#    #+#             */
/*   Updated: 2026/07/17 09:10:33 by erzhuo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "argv_env.h"

static void	print_redir(t_redir *redir)
{
	char	*s;

	while (redir)
	{
		s = "?";
		if (redir->type == INPUT)
			s = "<";
		else if (redir->type == OUTPUT)
			s = ">";
		else if (redir->type == HEREDOC)
			s = "<<";
		else if (redir->type == APPEND)
			s = ">>";
		printf(MAGENTA "  redir: %s %s\n" RESET, s, redir->file);
		redir = redir->next;
	}
}

int	print_argv(t_argv *head, t_env *env)
{
	t_argv	*tmp;
	int		x;
	int		i;

	x = 0;
	tmp = head;
	while (tmp)
	{
		if (expand_all(tmp, env))
			return (free_argv(head), free_env(env), exit(1), 0);
		printf(BLUE "--- cmd[%d] ---\n" RESET, x);
		i = 0;
		while (i < tmp->argc)
		{
			printf(GREEN "  argv[%d]: {%s}\n" RESET, i, tmp->argv[i]);
			i++;
		}
		print_redir(tmp->redir);
		printf("\n");
		x++;
		tmp = tmp->next;
	}
	return (1);
}

void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

static void	shell_loop(t_env *env)
{
	char	*line;
	t_argv	*head;
	int		i;

	while (1)
	{
		line = readline(GREEN "minishell> " RESET);
		if (!line)
			break ;
		if (*line)
			add_history(line);
		i = build_argv(line, env, &head);
		if (i == -1)
			continue ;
		if (i == 1 && print_argv(head, env))
		{
			env->exit_s = 0;
			free_argv(head);
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_env	env;

	(void)argc;
	(void)argv;
	if (!init_env(&env, envp))
		return (1);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_sigint);
	shell_loop(&env);
	free_env(&env);
	rl_clear_history();
	write(1, YELLOW "Exit minishell\n" RESET, 24);
	return (0);
}
