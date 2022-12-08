#include "../../include/minishell.h"

/* Born to code */
/* Source is a fuck */
/* Fix em' all 1970 */
/* I am UNIX man */
/* 410,757,864,530 DELETED LINES */

void	bltin_exit(t_cmd *cmd, t_shell *lambda)
{
	if (lambda->cmd_list && lambda->cmd_list->next)
		return ;
	if (lambda)
		dealloc_lambda(lambda);
	if (lambda->cmd_list)
		dealloc_cmds(lambda->cmd_list);
	if (lambda->env)
		ft_lstclear(&lambda->env, dealloc_env_element);
	if (cmd)
		;
	exit (lambda->status);
}
