#include "../../include/minishell.h"

void	dup2_cmd(t_cmd *cmd)
{
	dup2(cmd->input_fd, STDIN_FILENO);
	if (cmd->input_fd != STDIN_FILENO)
		close(cmd->input_fd);
	dup2(cmd->output_fd, STDOUT_FILENO);
	if (cmd->output_fd != STDOUT_FILENO)
		close(cmd->output_fd);
}

/* TODO: Double check if WIFSTOPPED is necessary */
int	get_wait_status(int stat_loc)
{
	if (WIFEXITED(stat_loc))
		return (WEXITSTATUS(stat_loc));
	else if (WIFSIGNALED(stat_loc))
		return (WTERMSIG(stat_loc));
	else if (WIFSTOPPED(stat_loc))
		return (WIFSTOPPED(stat_loc));
	return (0);
}
