#include "../includes/minishell.h"

// NOTE: Takes an t_env double pointer and returns
// the shell environment in form of string array.
// Used in cmd_constructor() to provide the shell env in
// the correct format for execve()
char	**env_to_strings(t_env **env)
{
	char	**envp;
	t_env	*env_element;
	int		iter;
	int		len;

	iter = 0;
	len = env_len(env);
	envp = malloc(sizeof(char *) * len);
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
	if (!cmd->args)
	{
		cmd_deallocator(cmd);
		msg_err("cmd_constructor()", FAILURE);
		return (NULL);
	}
	cmd->env = env_to_strings(env);
	if (!cmd->env)
	{
		cmd_deallocator(cmd);
		msg_err("cmd_constructor()", FAILURE);
		return (NULL);
	}
	cmd->path = get_path(prog_n, env);
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

// NOTE: INFO
// the t_pipe_blk is just a grouping of two commands piped together for the purpose of
// convenience.
// pipe_blk_alloc takes two strings and uses the cmd_constructor() to create
// two t_cmds, to be later executed.
// It then creates a pipe, and maps the output of cmd_one to the input of cmd_two

// NOTE In the case that the inputted line = (cat example.txt | grep "hello" | wc -l)
// The following layout will be used in the exec list:
// 	Note that "->" is used to represent output flow
// 	+----------------------------------------------+
// 	| (t_pipe_blk) cat example.txt -> grep "hello" |
// 	+----------------------------------------------+
// 	   | Output from the pipe_blk is mapped to the input of (t_cmd) wc -l.
// 	   V
// 	  +---------------+
// 	  | (t_cmd) wc -l |
// 	  +---------------+
// 	      |
// 	      V Final output.
// 	       +---------------+
// 	       | STDOUT_FILENO |
//         +---------------+

t_pipe_blk	*pipe_blk_alloc(char *cmd_one, char *cmd_two, int i, int o, t_env **env)
{
	t_pipe_blk	*pipe_blk;

	pipe_blk = malloc(sizeof(t_pipe_blk));
	if (!pipe_blk)
	{
		msg_err("pipe_blk_alloc()", FAILURE);
		return (NULL);
	}
	pipe_blk->cmd_one = cmd_constructor(cmd_one, env);
	pipe_blk->cmd_two = cmd_constructor(cmd_two, env);
	if (pipe(pipe_blk->pipe) == -1)
	{
		free(pipe_blk);
		msg_err("pipe_blk_alloc()", FAILURE);
		return (NULL);
	}
	pipe_blk->cmd_one->i_fd = pipe_blk->i_fd = i;
	pipe_blk->cmd_one->o_fd = pipe_blk->pipe[WRITE];
	pipe_blk->cmd_two->i_fd = pipe_blk->pipe[READ];
	pipe_blk->cmd_two->o_fd = pipe_blk->o_fd = o;
	return (pipe_blk);
}

// NOTE: Cleanly deallocates a pipe_blk and its constituent commands.
void	pipe_blk_dealloc(t_pipe_blk *pipe_blk)
{
	cmd_deallocator(pipe_blk->cmd_one);
	cmd_deallocator(pipe_blk->cmd_two);
	close(pipe_blk->pipe[READ]);
	close(pipe_blk->pipe[WRITE]);
	free(pipe_blk);
}
