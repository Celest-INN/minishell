#include "minishell.h"

int find_path(t_env *env)
{
    int i;

    i = 0;
    while (i < env->size)
    {
        if (ft_strncmp("PATH=", env->env[i], 5) == 0)
            return (env->env[i] + 5);
        i++;
    }
    return (NULL);
}

char  *path_append(char *begin, char *end, char *name)
{
    size_t len;
    char *path;

    if (*begin == ':')
        begin++;
    if (*end == NULL)
        end = begin + ft_strlen(begin);
    len = end - begin;
    path = malloc(sizeof(char)*(len + ft_strlen(name) + 2));
    if (!path)
        return (NULL);
    ft_memcpy(path, begin, len);
    path[len] = '/';
    ft_strcpy(path + len + 1, name);
    return (path);
}

int find_binary(t_env *env, char **argv)
{
    char    *path;
    char    *buf;
    char    *begin;
    char    *end;

    path = find_path(env);
    if (path == NULL)
        return (0);
    begin = path;
    buf = NULL; 
    while (begin != NULL)
    {
        end = ft_strchr(begin + 1, ':');
        free(buf);
        buf = path_append(begin, end, argv[0]);
        if (buf == NULL)
            return (-1);
        if (access(buf, X_OK) == 0)
        {
            (free(argv[0]), argv[0] = ft_strdup(buf));
            return (0);
        }
        begin = end;
    }
    return (0);
}

