#include "../inc/minishell.h"

int	execute(t_env *env, char **cmds)
{
	char	**paths;
	int		i;
	char	*ultpath;

	i = 0;
	paths = ft_split(get_cont("PATH", env), ':');
	// printf("----->%s", cmds[0]);
	while (paths[i])
	{
		ultpath = ft_strdup(paths[i]);
		ultpath = ft_strjoin(ultpath, "/");
		ultpath = ft_strjoin(ultpath, cmds[0]);
		if (execve(ultpath, cmds, ft_list_to_tab(env)) != -1)
			return (0);
		free(ultpath);
		i++;
	}
	ft_free_stab(paths);
	ft_free_stab(cmds);
	ft_putstr_fd("COMMAND NOT FOUND\n", 2);
	return (-1);
}

int	ft_exec_buildin(t_env *env, char **cmds)
{
	int	ret;

	ret = -1;
	if (ft_strcmp("env", cmds[0]) == 0)
		ret = ft_buildin_env(env);
	if (ft_strcmp("exit", cmds[0]) == 0)
		ret = ft_exit(env, cmds);
	if (ft_strcmp("pwd", cmds[0]) == 0)
		ret = ft_pwd(env);
	return (ret);
	// serach for status code for all the buildin created
}

int	ft_is_buildin(char **cmds)
{
	int	ret;

	ret = 0;
	if (ft_strcmp("env", cmds[0]) == 0)
		ret = 1;
	if (ft_strcmp("exit", cmds[0]) == 0)
		ret = 1;
	if (ft_strcmp("pwd", cmds[0]) == 0)
		ret = 1;
	if (ft_strcmp("cd", cmds[0]) == 0)
		ret = 1;
	if (ft_strcmp("export", cmds[0]) == 0)
		ret = 1;
	if (ft_strcmp("unset", cmds[0]) == 0)
		ret = 1;
	return (ret);
	// serach for status code for all the buildin created
}

// ca va beaucoup changer well shit
void	ft_command_handler(t_env *env, char *command)
{
	char	**cmds;
	pid_t	pid;

	pid = fork();
	cmds = ft_split(command, ' ');
	if (pid == -1)
		exit(1);
	else if (pid > 0)
	{
		waitpid(pid, 0, 0);
		kill(pid, SIGTERM);
	}
	else
	{
		if (ft_is_buildin(cmds) == 1)
			exit(ft_exec_buildin(env, cmds));
		else
			execute(env, cmds);
	}
}

int	ft_minishell(t_env *env)
{
	char	*command;

	(void)env;
	while (1)
	{
		ft_putstr_fd(">$", 1);
		ft_gnl(0, &command);
		// here the part of the queen herself
		ft_command_handler(env, command);
		free(command);
	}
}

int	main(int argc, char **argv, char **envp)
{	
	t_env	*env;

	(void)argc;
	(void)argv;
	// if (ft_set_signals() == 1)
	//   return (1);
	env = ft_put_env(envp);
	ft_minishell(env);
	return (0);
}
