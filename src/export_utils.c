/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ziyang <ziyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 14:55:18 by ziyang            #+#    #+#             */
/*   Updated: 2026/08/07 15:22:57 by ziyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_identifier(char *str, int *append)
{
	int	i;

	if (str == NULL || str[0] == '\0')
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (is_al(str[i]))
		i++;
	*append = 0;
	if (str[i] == '+' && str[i + 1] == '=')
	{
		*append = 1;
		return (1);
	}
	if (str[i] == '=' || str[i] == '\0')
		return (1);
	return (0);
}

void	sort_export_array(char **list, int size)
{
	char	*tmp;
	int		i;
	int		j;
	int		min;

	i = 0;
	while (i < size - 1)
	{
		min = i;
		j = i + 1;
		while (j < size)
		{
			if (export_cmp(list[j], list[min]))
				min = j;
			j++;
		}
		tmp = list[i];
		list[i] = list[min];
		list[min] = tmp;
		i++;
	}
}

char	**create_export_array(t_env *env, int *size)
{
	char	**list;
	int		i;
	int		j;

	list = malloc(sizeof(char *) * (env->size + 1));
	if (list == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (i < env->size)
	{
		if (!(env->env[i][0] == '_' && env->env[i][1] == '='))
		{
			list[j] = env->env[i];
			j++;
		}
		i++;
	}
	list[j] = NULL;
	*size = j;
	return (list);
}

void	print_export_variable(char *var, int fd)
{
	int	len;
	int	i;

	len = var_name_len(var);
	ft_putstr_fd("declare -x ", fd);
	i = 0;
	while (i < len)
	{
		ft_putchar_fd(var[i], fd);
		i++;
	}
	if (var[len] == '=')
	{
		ft_putstr_fd("=\"", fd);
		ft_putstr_fd(var + len + 1, fd);
		ft_putchar_fd('"', fd);
	}
	ft_putchar_fd('\n', fd);
}

int	print_export_list(t_env *env, int fd)
{
	char	**list;
	int		size;
	int		i;

	list = create_export_array(env, &size);
	if (list == NULL)
		return (1);
	sort_export_array(list, size);
	i = 0;
	while (i < size)
	{
		print_export_variable(list[i], fd);
		i++;
	}
	free(list);
	return (0);
}
