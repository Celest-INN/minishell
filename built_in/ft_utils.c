/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ziyang <ziyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 16:45:20 by ziyang            #+#    #+#             */
/*   Updated: 2026/07/18 17:33:02 by ziyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	update_dir(char *dir, t_env *env)
{
	char	*tmp;

	if (dir == NULL)
		return (0);
	tmp = ft_strdup(dir);
	if (tmp == NULL)
		return (-1);
	if (update_oldpwd(env) == -1)
		return (free(tmp), -1);
	if (chdir(tmp))
	{
		free(tmp);
		perror("chdir");
		return (-1);
	}
	free(tmp);
	if (update_pwd(env))
		return (-1);
	return (0);
}
