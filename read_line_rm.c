#include "minishell.h"

char    *read_line(char *prompt)
{
    char   *line;
    int     i;

    if (isatty(STDIN_FILENO))
        return (readline(prompt));
    line = get_next_line(STDIN_FILENO);
    if (line == NULL)
        return (NULL);
    i = ft_strlen(line);
    if (line[i - 1] == '\n')
        line[i - 1] = '\0';
    return (line);
}