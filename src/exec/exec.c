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

int	executor(t_exec_element *head)
{
	t_exec_element	*list;
	t_exec_element	*next;

	list = head;
	if (!list->next)
	{
		if (list->type == tkn_cmd)
		{
			execute_command(list->value);
		}
	}
	while (list->next)
	{
		if (list->type == tkn_pipe)
		{
			next = list->next;
		}
		list = next;
	}
	return (SUCCESS);
}
