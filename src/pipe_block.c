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
		msg_err("cmd_constructor()", FAILURE);
		return (NULL);
	}
	cmd->env = env;
	cmd->path = get_path(prog_n, env);
	if (!cmd->path)
	{
		free(cmd->args);
		free(cmd);
		msg_err("cmd_constructor()", FAILURE);
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

/* NOTE: Assumes file descriptors and cmds provided are already opened/allocated. */
t_pipe_blk	*pipe_blk_alloc(t_cmd *cmd_one, t_cmd *cmd_two, int i, int o)
{
	t_pipe_blk	*pipe_blk;

	pipe_blk = malloc(sizeof(t_pipe_blk));
	if (!pipe_blk)
	{
		msg_err("pipe_blk_alloc()", FAILURE);
		return (NULL);
	}
	pipe_blk->i_fd = i;
	pipe_blk->o_fd = o;
	pipe_blk->cmd_one = cmd_one;
	pipe_blk->cmd_two = cmd_two;
	if (pipe(pipe_blk->pipe) == -1)
	{
		free(pipe_blk);
		msg_err("pipe_blk_alloc()", FAILURE);
		return (NULL);
	}
	cmd_one->i_fd = pipe_blk->i_fd;
	cmd_one->o_fd = pipe_blk->pipe[WRITE];
	cmd_two->i_fd = pipe_blk->pipe[READ];
	cmd_two->o_fd = pipe_blk->o_fd;
	return (pipe_blk);
}

void	pipe_blk_dealloc(t_pipe_blk *pipe_blk)
{
	cmd_deallocator(pipe_blk->cmd_one);
	cmd_deallocator(pipe_blk->cmd_two);
	close(pipe_blk->pipe[READ]);
	close(pipe_blk->pipe[WRITE]);
	free(pipe_blk);
}
