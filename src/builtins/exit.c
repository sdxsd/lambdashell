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
	char	*error_msg;

	if (!cmd->args[1])
		return (stop_void());
	if (!ft_atoi_safe(cmd->args[1], &exit_status))
	{
		error_msg = ft_strjoin_array((char *[]){PREFIX": exit: ", cmd->args[1], ": numeric argument required\n", NULL});
		// TODO: What to do if error_msg is NULL?
		if (error_msg)
		{
			ft_putstr_fd(error_msg, STDERR_FILENO);
		}
		status = 255;
		return (stop_void());
	}
	else if (!cmd->args[2])
	{
		status = exit_status;
		return (stop_void());
	}
	else
	{
		ft_putstr_fd(PREFIX": exit: too many arguments\n", STDERR_FILENO);
		status = 1;
	}
}
