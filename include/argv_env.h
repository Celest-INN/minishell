/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv_env.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erzhuo <erzhuo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 09:06:48 by erzhuo            #+#    #+#             */
/*   Updated: 2026/08/10 15:12:48 by erzhuo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARGV_ENV_H
# define ARGV_ENV_H

# include "libft.h"
# include <errno.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define MAGENTA "\033[35m"
# define CYAN "\033[36m"
# define WHITE "\033[37m"
# define RESET "\033[0m"

/*
** 精简后的 token 类型: 只有6种
** WORD     = 普通词 (命令名、参数、文件名)
** PIPE     = |
** INPUT    = <
** OUTPUT   = >
** HEREDOC  = <<
** APPEND   = >>
*/
typedef enum e_token_type
{
	WORD,
	PIPE,
	INPUT,
	OUTPUT,
	HEREDOC,
	APPEND,
}					t_token_type;

/*
** lexer 产出: 每个 token 一个节点
*/
typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}					t_token;

/*
** 重定向链表: 挂在 t_argv 的 redir 字段上
** type = INPUT/OUTPUT/HEREDOC/APPEND
** file = 目标文件名 (或 heredoc 分隔符)
*/
typedef struct s_redir
{
	t_token_type	type;
	char			*file;
	struct s_redir	*next;
}					t_redir;

/*
** 一条简单命令 (管道之间的部分)
** argv  = execve 需要的参数数组, 不含重定向
** redir = 这条命令的重定向链表
** argc  = argv 中参数的个数
** next  = 管道右边的下一条命令
*/
typedef struct s_argv
{
	char			**argv;
	t_redir			*redir;
	int				argc;
	struct s_argv	*next;
}					t_argv;

typedef struct s_env
{
	char			**env;
	int				cap;
	int				size;
	int				exit_s;
}					t_env;

// init_env.c
int					init_env(t_env *env, char **envp);

// lexer_helper.c
int					is_operator(char *str);
int					is_redir_type(t_token_type type);
int					is_double_op(t_token_type type);
int					token_len(char *str);
char				*token_strndup(const char *s, int n);

// lexer.c
t_token				*make_token(char *str, t_token_type type);
int					link_token(t_token **h, t_token **cur, t_token_type t,
						char *s);
t_token				*lexer(char *line, t_env *env);

// syntax_check.c
int					precheck_line(char *line);
int					is_op(t_token_type x);
char				*syntax_check(t_token *token);
int					syntax_error(char *line, t_token *token, t_env *env);

// parser_helper.c
int					count_cmd_argc(t_token *token);
int					build_redirs(t_token *token, t_redir **head);
int					build_argv_arr(t_argv *node, t_token *token);

// parser.c
t_argv				*parse_command(t_token **token);
t_argv				*make_argv(t_token *token);
int					build_argv(char *line, t_env *env, t_argv **out);

// expander_helper_var.c
char				*find_var(char *str, t_env *env);
int					is_quote_char(char c, int *sq, int *dq);
int					append_n(char **dst, char *src, int n);
int					append_var(char **out, char **str, int *i, t_env *env);

// expander.c
int					expand_home(t_argv *curt, t_env *env);
int					expand_str(char **str, t_env *env, int *quoted, int hd);
int					expander_helper(char **str, t_env *env);
int					expander(t_argv *curt, t_env *env);
int					expand_all(t_argv *curt, t_env *env);

// rm_char.c
int					check_q(char c, int *q_s, int *q_d);
void				int_init(int *i, int n);
void				rm_char_helper(char **str);
void				rm_char(t_argv *curt);

// trimmer.c
void				trim_q(char **s);
int					rm_empty(t_argv *curt, int i);
int					expand_redir(t_argv *curt, t_env *env);

// helper_itoa.c
int					is_al(char c);
int					is_var_start(char c);

// helper_free.c
void				free_strstr(char **s);
void				free_env(t_env *env);
void				free_tokens(t_token *head);
void				free_redir(t_redir *head);
void				free_argv(t_argv *head);

#endif
