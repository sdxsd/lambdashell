#include "../../include/minishell.h"

/* Born to code */
/* Source is a fuck */
/* Fix em' all 1970 */
/* I am UNIX man */
/* 410,757,864,530 DELETED LINES */

void	bltin_exit(t_cmd *cmd, t_shell *lambda)
{
	if (lambda)
		dealloc_lambda(lambda);
	// TODO: Make sure exit args are used.
	if (cmd)
		;
	rl_clear_history();
	exit (lambda->status);
}
