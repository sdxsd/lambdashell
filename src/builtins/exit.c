#include "../../include/minishell.h"

/* Born to code */
/* Source is a fuck */
/* Fix em' all 1970 */
/* I am UNIX man */
/* 410,757,864,530 DELETED LINES */

void	bltin_exit(t_cmd *cmd, t_shell *lambda)
{
	int	exit_status;

	if (!cmd->args[1])
	{
		stop();
		return ;
	}
	if (!cmd->args[2])
	{
		// TODO: Use Sander's atoi that allows telling
		// whether 0 means an error occurred or the input was "0"
		exit_status = ft_atoi(cmd->args[1]);
		lambda->status = exit_status;
		return ;
	}
	// TODO: Print on stderr instead
	ft_putstr("λ: exit: too many arguments\n");
	lambda->status = 1;
	return ;
}
