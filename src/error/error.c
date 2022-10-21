#include "../includes/minishell.h"

int	msg_err(char *s, int ret)
{
	perror(s);
	return (ret);
}

void	*null_msg_err(char *s)
{
	msg_err(s, 0);
	return (NULL);
}
