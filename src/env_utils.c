/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ziyang <ziyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 12:19:38 by ziyang            #+#    #+#             */
/*   Updated: 2026/08/07 14:55:12 by ziyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_cwd(void)
{
	char	*cwd;
	int		size;

	size = BUFFER_SIZE;
	cwd = (char *)malloc(size);
	if (cwd == NULL)
		return (NULL);
	while (getcwd(cwd, size) == NULL)
	{
		if (errno == EACCES || errno == ENAMETOOLONG || errno == ENOENT
			|| errno == ENOMEM)
		{
			perror("getcwd: cannot access current directory");
			free(cwd);
			return (NULL);
		}
		free(cwd);
		size *= 2;
		cwd = (char *)malloc(size);
		if (cwd == NULL)
			return (NULL);
	}
	return (cwd);
}

int	set_cwd_var(t_env *env, char *pwd)
{
	char	*cwd;
	char	*var;
	int		ret;

	cwd = get_cwd();
	if (cwd == NULL)
		return (0);
	var = ft_strjoin(pwd, cwd);
	free(cwd);
	if (var == NULL)
		return (-1);
	ret = env_set(env, var);
	free(var);
	if (ret)
		return (-1);
	else
		return (0);
}

int	update_oldpwd(t_env *env)
{
	return (set_cwd_var(env, "OLDPWD="));
}

int	update_pwd(t_env *env)
{
	return (set_cwd_var(env, "PWD="));
}

char	*get_env_value(t_env *env, char *var)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(var);
	while (i < env->size)
	{
		if ((ft_strncmp(var, env->env[i], len) == 0) && env->env[i][len] == '=')
			return (&env->env[i][len + 1]);
		i++;
	}
	return (NULL);
}
