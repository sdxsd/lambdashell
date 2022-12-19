#include "../../include/minishell.h"

/* Born to code */
/* Source is a fuck */
/* Fix em' all 1970 */
/* I am UNIX man */
/* 410,757,864,530 DELETED LINES */

void	bltin_exit(t_cmd *cmd, t_shell *lambda)
{
	int		exit_status;
	char	*error_msg;

	if (!cmd->args[1])
	{
		stop();
		return ;
	}
	if (!cmd->args[2])
	{
		if (!ft_atoi_safe(cmd->args[1], &exit_status))
		{
			error_msg = ft_strjoin_array((char *[]){PREFIX": exit: ", cmd->args[1], ": numeric argument required\n", NULL});
			// TODO: What to do if error_msg is NULL?
			if (error_msg)
			{
				ft_putstr_fd(error_msg, STDERR_FILENO);
			}
			lambda->status = 255;
			return ;
		}

		lambda->status = exit_status;
		return ;
	}
	ft_putstr_fd(PREFIX": exit: too many arguments\n", STDERR_FILENO);
	lambda->status = 1;
	return ;
}
