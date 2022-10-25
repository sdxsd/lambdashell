#include "../../include/minishell.h"
#include <unistd.h>

void	cd(t_cmd *cmd)
{
	if (chdir(cmd->args[1]))
	{
		msg_err("cd", FAILURE);
	}
}
