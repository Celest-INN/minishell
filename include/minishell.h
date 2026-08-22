/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erzhuo <erzhuo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/09 19:54:54 by ziyang            #+#    #+#             */
/*   Updated: 2026/08/22 20:09:07 by erzhuo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "argv_env.h"
# include "libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

# define PROMPT "minishell> "

# define BUFFER_SIZE 1024

extern int	g_sig;

typedef struct s_pipex
{
	t_env	*env;
	t_argv	*argv;
	char	*path;
	int		exit_status;
	int		pid;
	int		fd_in;
	int		fd_out;
}			t_pipex;

void		handle_sigint(int sig);
int			builtin_exit(t_argv *argv, t_pipex *pipex);
int			builtin_cd(t_argv *cmd, t_pipex *pipex);
int			exec_built_in(t_argv *cmd, t_pipex *pipex);
int			path_nopermission_execute(char *cmd);
int			path_cmd_nofound(char *cmd);
int			path_checker(char *path, t_env *env);
int			find_binary(t_env *env, char **argv);
void		pipex_init(t_pipex *pipex, t_argv *cmd, t_env *env);
void		wait_child(t_pipex *pipex);
int			open_redir(t_redir *redir, t_pipex *pipex);
int			exec(t_argv *cmds, t_pipex *pipex);
void		exit_free(t_pipex *pipex, int exits);
int			exit_free_child(int exit_s, t_pipex *pipex);
int			update_dir(char *dir, t_env *env);
int			get_heredoc(int fdhd, char *lim, t_env *env);
void		unlink_tmp_heredoc(t_argv *cmd);
int			all_heredoc(t_argv *cmd, t_pipex *pipex);

int			update_directory(char *dir, t_env *env);
int			builtin_cd(t_argv *cmd, t_pipex *pipex);
int			builtin_echo(t_argv *cmd, t_pipex *pipex);
int			builtin_env(t_argv *cmd, t_pipex *pipex);
int			builtin_exit(t_argv *argv, t_pipex *pipex);
int			builtin_pwd(t_pipex *pipex);
int			builtin_unset(t_argv *cmd, t_pipex *pipex);
int			env_var_index(t_env *env, char *v, int len);
int			env_set(t_env *env, char *v);
int			append_env(t_env *env, char *var);
char		*get_cwd(void);
int			update_oldpwd(t_env *env);
int			update_pwd(t_env *env);
char		*get_env_value(t_env *env, char *var);
void		free_pointer(char **s);
void		argv_free(t_argv *cmd);
void		env_free(t_env *env);
int			builtin_export(t_argv *cmd, t_pipex *pipex);
int			var_name_len(char *s);
int			check_identifier(char *str, int *append);
int			print_export_list(t_env *env, int fd);
int			export_cmp(char *a, char *b);
void		close_fd(int fd);
void		check_file_error(char *file, int acc);
void		heredoc_sighandler(int sig);
void		update_fd(int *oldfd, int newfd);

#endif
