#include "../../include/minishell.h"

// Born to code
// Source is a fuck
// Fix em' all 1970
// I am UNIX man
// 410,757,864,530 DELETED LINES

void	bltin_exit(int status, t_list *cmds, t_shell *lambda)
{
	if (lambda)
		dealloc_lambda(lambda);
	// TODO: Write dealloc_cmds()
	if (cmds)
		dealloc_cmds(cmds);
	exit (status);
}
