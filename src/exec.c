#include "../includes/minishell.h"
#include <sys/wait.h>

/* NOTE: INFO */
/* Takes a t_cmd and executes it. */
int	execute_command(t_cmd *cmd)
{
	dup2(cmd->i_fd, STDIN_FILENO);
	dup2(cmd->o_fd, STDOUT_FILENO);
	if (execve(cmd->path, cmd->args, cmd->env) == -1)
	{
		msg_err("execute_command()", FAILURE);
		cmd_deallocator(cmd);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	execute_pipe_blk(t_pipe_blk *pipe_blk)
{
	int	pid;

	pid = fork();
	if (pid == FORK_FAILURE)
		return (msg_err("execute_pipe_blk()", FAILURE));
	if (pid == FORK_CHILD)
	{
		close(pipe_blk->pipe[WRITE]);
		if (execute_command(pipe_blk->cmd_two))
			exit (msg_err("execute_pipe_blk()", -1));
	}
	close(pipe_blk->pipe[READ]);
	if (execute_command(pipe_blk->cmd_one))
		exit (msg_err("execute_pipe_blk()", -1));
	waitpid(pid, NULL, 1);
	return (SUCCESS);
}

int	executor(t_exec_element *head)
{
	t_exec_element	*list;
	t_exec_element	*next;

	list = head;
	while (list->next)
	{
		if (list->type == tkn_pipe)
		{
			next = list->next;
			if (next->type == tkn_pipe)
			{
				lnk_pipe_blk((t_pipe_blk *)list->value, (t_pipe_blk *)next->value);
			}
		}
	}
}
