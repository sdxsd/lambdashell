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
		msg_err("cmd_constructor()", 1);
		return (NULL);
	}
	cmd->env = env;
	cmd->path = get_path(prog_n, env);
	if (!cmd->path)
	{
		free(cmd->args);
		free(cmd);
		msg_err("cmd_constructor()", 1);
		return (NULL);
	}
	return (cmd);
}

void	cmd_deallocator(t_cmd *cmd)
{
	free_ptr_array(cmd->args);
	free(cmd->path);
	free(cmd);
}

t_pipe_blk	*pipe_block_constructor()
{

}
