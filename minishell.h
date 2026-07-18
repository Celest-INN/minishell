#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdint.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <stdlib.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/types.h>
# include <unistd.h>
# include <sys/wait.h>
# include <termios.h>
# include <errno.h>
# include <sys/stat.h>

# define PROMPT "minishell>"

typedef enum e_token_type
{
	WORD,
	PIPE,
	INPUT,
	OUTPUT,
	HEREDOC,
	APPEND,
}	t_token_type;

typedef struct s_redir
{
    t_token_type    type; 
    char            *file; 
    struct s_redir  *next;
}    t_redir;

typedef struct s_argv  
{
    char            **argv;
	t_redir			*redir;
    int              argc;  
    struct s_argv    *next;
}    t_argv;

typedef struct s_env
{
	char   **env;
	int    cap;
	int    size;
	int    exit_s;
}   t_env;

typedef struct s_pipex
{
	t_env	*env;
	t_argv	*argv;
	char	*path;
    int		exit_status;
	int		pid;
	int		fd_in;
	int		fd_out;
}	t_pipex;

#endif