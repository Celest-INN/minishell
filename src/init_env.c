/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ziyang <ziyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 09:09:13 by erzhuo            #+#    #+#             */
/*   Updated: 2026/08/07 15:15:02 by ziyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "argv_env.h"

int	init_env(t_env *env, char **envp)
{
	int	i;

	i = 0;
	env->size = 0;
	env->exit_s = 0;
	env->cap = 8;
	while (envp[i++])
		env->cap = i * 2;
	env->env = malloc(sizeof(char *) * env->cap);
	if (!env->env)
		return (free_env(env), 0);
	i = 0;
	while (envp[i])
	{
		env->env[i] = ft_strdup(envp[i]);
		if (!env->env[i])
			return (free_env(env), 0);
		i++;
	}
	env->env[i] = NULL;
	env->size = i;
	return (1);
}
