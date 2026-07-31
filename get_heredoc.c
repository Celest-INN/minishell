#include "minishell.h"

void  free_lines(char **lines)
{
    int i;

    i = 0;
    if (!lines)
        return ;
    while (lines[i])
    {
        free(lines[i]);
        i++;
    }
    free(lines);
}

int process_line(char **line, char *lim, int fd, t_env *env)
{
    if (!ft_strcmp(*line, lim))
        return (1);
    if (env && !expandre_helper(line, env))
        return (-1);
    ft_putend_fd(*line, fd);
    return (0);
}

int  check_lines(char *s, char *lim, int fd, t_env *env)
{
    char	**lines;
	int		i;
	int		result;

	if (!ft_strchr(s, '\n'))
	{
		result = process_line(&s, lim, fd, env);
		return (free(s), result);
	}
	lines = ft_split(s, '\n');
	free(s);
	if (!lines)
		return (-1);
	i = 0;
	while (lines[i])
	{
		result = process_line(&lines[i], lim, fd, env);
		if (result)
			return (free_lines(lines), result);
		i++;
	}
	return (free_lines(lines), 0);
}
void	heredoc_warning(char *lim)
{
	ft_putstr_fd("minishell: warning: heredoc is delimited by EOF wanted ",
		STDERR_FILENO);
	ft_putendl_fd(lim, STDERR_FILENO);
}

int get_heredoc(int fdhd, char *lim, t_env *env)
{
    char *line;
    char *lim2;
    int r;

    lim2 = ft_strdup(lim);
    if (!lim2)
        return (close(fdhd), -1);
    trim_q(&lim);
    if (ft_strcmp(lim, lim2) != 0)
        env = NULL;
    line = read_line("> ");
    //line = readline("> ")
    while (line)
    { 
        r = check_lines(line, lim, fdhd, env);
		if (r == -1)
			return (free(lim2), close(fdhd), -1);
		if (r == 1)
			break ;
		line = read_line("> ");
        //line = readline("> ");
	}
	if (!line)
		heredoc_warning(lim);
	return (free(lim2), close(fdhd), 0);
}
