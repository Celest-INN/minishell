#include "minishell.h"

int cd_no_arg(t_env *env)
{
    char *home_pwd;

    home_pwd = get_env(env, "HOME");
    if (home_pwd == NULL)
    {
        ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
        return (-1);
    }
    return (update_dir(home_pwd, env));
}

int    cd_is_directory(char *name)
{
    struct stat st;
    char        *tmp;

    if (stat(name, &st) == -1)
    {
        tmp = ft_strjoin("minishell: cd: ", name);
        perror(tmp);
        free(tmp);
        return (-1);
    }
    if (!S_ISDIR(st.st_mode))
    {
        tmp = ft_strjoin("minishell: cd: ", name);
        ft_putstr_fd(tmp, STDERR_FILENO);
        ft_putstr_fd(": Not a directory\n", STDERR_FILENO);
        free(tmp);
        return (-1);
    }
    return (0);
}

int     ft_cd(t_argv *cmd, t_pipex *pipex)
{
    int r;

    if (cmd->argc > 2)
    {
        ft_putstr_fd("minishell: cd: too many arguments\n", STDERR_FILENO);
        return (exit_free_child(1, pipex));
    }
    if (cmd->argv == 1)

}
