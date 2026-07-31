#include "minishell.h"

static int	exec_builtin_exit(t_argv *cmd, t_pipex *pipex)
{
	int	r;

	r = ft_exit(cmd, pipex->fd_in, pipex->fd_out);
	if (r == -1)
	{
		pipex->exit_status = 1;
		return (-3);
	}
	else if (r >= 0)
		pipex->exit_status = r;
	return (-2);
}

int	exec_builtin(t_argv *cmd, t_pipex *pipex)
{
	if (!ft_strcmp(cmd->argv[0], "cd"))
		return (ft_cd(cmd, pipex));
	if (!ft_strcmp(cmd->argv[0], "pwd"))
		return (ft_pwd(pipex));
	if (!ft_strcmp(cmd->argv[0], "echo"))
		return (ft_echo(cmd, pipex));
	if (!ft_strcmp(cmd->argv[0], "export"))
		return (ft_export(cmd, pipex));
	if (!ft_strcmp(cmd->argv[0], "unset"))
		return (ft_unset(cmd,pipex));
	if (!ft_strcmp(cmd->argv[0], "env"))
		return (ft_env(cmd, pipex));
	if (!ft_strcmp(cmd->argv[0], "exit"))
		return (exec_builtin_exit(cmd, pipex));
	return (0);
}
