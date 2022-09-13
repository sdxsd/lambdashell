#include "../includes/minishell.h"

t_cmd	*cmd_constructor(char *prog_n, t_env **env)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->i_fd = STDIN_FILENO;
	cmd->o_fd = STDOUT_FILENO;
	cmd->args = ft_split(prog_n, ' ');
	if (!cmd->args)
	{
		free(cmd);
		return (NULL);
	}
	cmd->env = env;
	cmd->path = get_path(prog_n, env);
	if (!cmd->path)
	{
		free(cmd->args);
		free(cmd);
		return (NULL);
	}
}
