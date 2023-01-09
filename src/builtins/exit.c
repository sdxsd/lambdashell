#include "../../include/minishell.h"

/* Born to code */
/* Source is a fuck */
/* Fix em' all 1970 */
/* I am UNIX man */
/* 410,757,864,530 DELETED LINES */

// These ones do exit in Bash: `exit 0`, `exit a 2`, `exit a b`
// These ones don't exit in Bash: `exit 4 2`, `exit 4 a`
void	bltin_exit(t_cmd *cmd)
{
	int		exit_status;

	if (!cmd->args[1])
		return (stop_void());
	if (!ft_atoi_safe(cmd->args[1], &exit_status))
	{
		prefixed_error("exit: ");
		print_error(cmd->args[1]);
		print_error(": numeric argument required\n");
		g_status = 2;
		return (stop_void());
	}
	else if (!cmd->args[2])
	{
		g_status = exit_status;
		return (stop_void());
	}
	else
	{
		prefixed_error("exit: too many arguments\n");
		g_status = 127;
	}
}
