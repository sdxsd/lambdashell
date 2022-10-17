#include "../includes/minishell.h"

// NOTE: INFO
// cmd_constructor() is the constructor for the type
// t_cmd, which contains all the data required for execve() to be called.
// cmd_constructor() is used in the construction of singular commands.
// Also used in the creation of a pipe_blk

// NOTE: USAGE
// The t_cmd type is used in the program to execute external binaries
// cleanly and without error. All errors surrounding missing binaries
// and non-functioning/non-existant paths should be caught here.
// The function operates in three stages.
// First assigning the args by splitting the prog_n string.
// Then using the env_to_string() function to assign the shell environment.
// Finally getting the full path to the binary returning the fully formed t_cmd.
// If any part fails, all memory will be freed before returning.
// Memory leaks SHOULD be impossible.
t_cmd	*cmd_constructor(char *prog_n_args, t_env **env)
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
	cmd->args = ft_split(prog_n_args, ' ');
	if (!cmd->args)
	{
		cmd_deallocator(cmd);
		msg_err("cmd_constructor()", FAILURE);
		return (NULL);
	}
	cmd->env = env_to_arrays(env);
	if (!cmd->env)
	{
		cmd_deallocator(cmd);
		msg_err("cmd_constructor()", FAILURE);
		return (NULL);
	}
	cmd->path = get_path(cmd->args[0], env);
	if (!cmd->path)
	{
		msg_err(cmd->args[0], FAILURE);
		cmd_deallocator(cmd);
		return (NULL);
	}
	return (cmd);
}

// NOTE: Cleanly deallocates a t_cmd.
void	cmd_deallocator(t_cmd *cmd)
{
	if (cmd->env)
		free_ptr_array(cmd->env);
	if (cmd->args)
		free_ptr_array(cmd->args);
	if (cmd->path)
		free(cmd->path);
	free(cmd);
}
