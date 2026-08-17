/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ziyang <ziyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 11:54:11 by ziyang            #+#    #+#             */
/*   Updated: 2026/08/13 20:14:55 by ziyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_path(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->size)
	{
		if (ft_strncmp("PATH=", env->env[i], 5) == 0)
			return (env->env[i] + 5);
		i++;
	}
	return (NULL);
}

char	*path_append(char *begin, char *end, char *name)
{
	size_t	len;
	char	*path;

	if (*begin == ':')
		begin++;
	if (end == NULL)
		end = begin + ft_strlen(begin);
	len = end - begin;
	path = malloc(sizeof(char) * (len + ft_strlen(name) + 2));
	if (!path)
		return (NULL);
	ft_memcpy(path, begin, len);
	path[len] = '/';
	ft_strcpy(path + len + 1, name);
	return (path);
}

int	is_relative_path(char *path)
{
	if (path[0] == '.' && path[1] == '\0')
		return (1);
	if (path[0] == '.' && path[1] == '.' && path[2] == '\0')
		return (1);
	if (path[0] == '.' && path[1] == '/')
		return (1);
	if (path[0] == '/')
		return (1);
	return (0);
}

char	*make_relative_path(char *cmd)
{
	char	*tmp;

	tmp = ft_strjoin("./", cmd);
	free(cmd);
	return (tmp);
}

int	find_binary(t_env *env, char **argv)
{
	char	*path;
	char	*buf;
	char	*begin;
	char	*end;

	if (argv[0][0] == '\0' || is_relative_path(argv[0]))
		return (0);
	path = find_path(env);
	if (path == NULL || path[0] == '\0')
		return (argv[0] = make_relative_path(argv[0]), 0);
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
			return (free(argv[0]), argv[0] = ft_strdup(buf), free(buf), 0);
		begin = end;
	}
	return (free(buf), 0);
}
