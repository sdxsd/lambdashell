#include "../includes/minishell.h"

char	**env_to_strings(t_env **env)
{
	char	**envp;
	t_env	*env_element;
	int		iter;
	int		len;

	iter = 0;
	envp = malloc(sizeof(char *) * env_len(env));
	env_element = *env;
	if (!envp)
	{
		msg_err("env_to_strings()", FAILURE);
		return (NULL);
	}
	while (iter < len)
	{
		envp[iter] = env_element->val;
		env_element = env_element->next;
		iter++;
	}
	return (envp);
}

static int	check_cmd_malloc(t_cmd *cmd)
{
	if (!cmd->args)
	{
		free(cmd);
		return (msg_err("cmd_constructor()", FAILURE));
	}
	if (!cmd->env)
	{
		free_ptr_array(cmd->args);
		return (msg_err("cmd_constructor()", FAILURE));
	}
	if (!cmd->path)
	{
		free_ptr_array(cmd->args);
		free_ptr_array(cmd->env);
		return (msg_err("cmd_constructor()", FAILURE));
	}
	return (SUCCESS);
}

/* NOTE: Data type of env needs to be decided on */
/* execve takes env as a string of characters. */
t_cmd	*cmd_constructor(char *prog_n, t_env **env)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
	{
		msg_err("cmd_constructor()", FAILURE);
		return (NULL);
	}
	cmd->i_fd = STDIN_FILENO;
	cmd->o_fd = STDOUT_FILENO;
	cmd->args = ft_split(prog_n, ' ');
	if (check_cmd_malloc(cmd))
		return (NULL);
	cmd->env = env_to_strings(env);
	if (check_cmd_malloc(cmd))
		return (NULL);
	cmd->path = get_path(prog_n, env);
	if (check_cmd_malloc(cmd))
		return (NULL);
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
	pipe_blk->cmd_one = cmd_one;
	pipe_blk->cmd_two = cmd_two;
	if (pipe(pipe_blk->pipe) == -1)
	{
		free(pipe_blk);
		msg_err("pipe_blk_alloc()", FAILURE);
		return (NULL);
	}
	cmd_one->i_fd = pipe_blk->i_fd = i;
	cmd_one->o_fd = pipe_blk->pipe[WRITE];
	cmd_two->i_fd = pipe_blk->pipe[READ];
	cmd_two->o_fd = pipe_blk->o_fd = o;
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
