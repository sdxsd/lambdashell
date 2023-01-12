#include "../../include/minishell.h"
#include <errno.h>

static t_status	execute_child(int i_fd, t_list *cmds, t_shell *lm, int tube[2])
{
	t_cmd	*cmd;

	signal_handler_child_set();
	cmd = cmds->content;
	if (cmds->next)
		close(tube[READ]);
	if (i_fd != -1)
		cmd->input_fd = i_fd;
	if (cmds->next)
		cmd->output_fd = tube[WRITE];
	if (cmd->path && ft_strchr(cmd->path, '/'))
		if (execute_command(cmd, lm) == ERROR)
			dealloc_and_exit(g_status, lm);
	if (execute_builtin(cmd, lm) == ERROR)
		dealloc_and_exit(g_status, lm);
	exit(g_status);
	return (OK);
}

static t_status	forkxec(int *p, int i_fd, t_list *cmds, t_shell *lm)
{
	int	t[2];

	if (cmds->next && pipe(t) == -1)
		return (prefixed_perror("execute_complex_command()"));
	*p = fork();
	if (*p == FORK_FAILURE)
		return (prefixed_perror("fork"));
	if (*p == FORK_CHILD)
		if (execute_child(i_fd, cmds, lm, t) == ERROR)
			dealloc_and_exit(g_status, lm);
	disable_signals();
	if (cmds->next)
		close(t[WRITE]);
	if (i_fd != -1)
		close(i_fd);
	if (cmds->next && exec_complex_cmd(t[READ], cmds->next, lm) != OK)
	{
		if (errno != EAGAIN)
			return (prefixed_perror("execute_complex_command()"));
		return (ERROR);
	}
	return (OK);
}

// TODO: Right now only the parent is closing the read end!!
// Double check if this is an issue.
t_status	exec_complex_cmd(int i_fd, t_list *cmds, t_shell *lambda)
{
	pid_t	pid;
	int		stat_loc;

	if (forkxec(&pid, i_fd, cmds, lambda) == ERROR)
		return (ERROR);
	waitpid(pid, &stat_loc, 0);
	if (!cmds->next)
		g_status = get_wait_status(stat_loc);
	return (OK);
}
