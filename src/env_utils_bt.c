/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_bt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ziyang <ziyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 12:19:35 by ziyang            #+#    #+#             */
/*   Updated: 2026/08/07 14:51:34 by ziyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	var_name_len(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	return (i);
}

int	env_var_index(t_env *env, char *v, int len)
{
	int	i;

	i = 0;
	if (env == NULL || v == NULL)
		return (0);
	while (i < env->size)
	{
		if ((ft_strncmp(v, env->env[i], len) == 0) && env->env[i][len] == '=')
			return (i);
		i++;
	}
	return (env->size);
}

int	env_grow(t_env *env)
{
	char	**new_env;
	int		new_cap;

	new_cap = env->cap * 2;
	new_env = malloc(sizeof(char *) * (new_cap + 1));
	if (new_env == NULL)
		return (1);
	ft_memcpy(new_env, env->env, sizeof(char *) * env->size);
	new_env[env->size] = NULL;
	free(env->env);
	env->env = new_env;
	env->cap = new_cap;
	return (0);
}

int	env_set(t_env *env, char *v)
{
	int	index;
	int	len;

	len = var_name_len(v);
	if (v[len] == '\0')
		return (0);
	index = env_var_index(env, v, len);
	if (index == env->size)
	{
		if (env->size == env->cap && env_grow(env))
			return (1);
		env->size++;
		env->env[env->size] = NULL;
	}
	else
		free(env->env[index]);
	env->env[index] = ft_strdup(v);
	return (env->env[index] == NULL);
}

int	append_env(t_env *env, char *var)
{
	char	*new_var;
	int		i;
	int		len;

	len = var_name_len(var);
	i = env_var_index(env, var, len);
	if (i == env->size)
	{
		new_var = ft_strdup(var);
		if (new_var == NULL)
			return (1);
		ft_memmove(new_var + len, new_var + len + 1, ft_strlen(new_var + len));
		i = env_set(env, new_var);
		free(new_var);
		return (i);
	}
	new_var = ft_strjoin(env->env[i], var + len + 2);
	if (new_var == NULL)
		return (1);
	free(env->env[i]);
	env->env[i] = new_var;
	return (0);
}
