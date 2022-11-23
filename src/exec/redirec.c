#include "../include/minishell.h"
#include <stdlib.h>

// NOTE: Thine fruit need not be begotten so.


static int	n_redirecs(char *prog)
{
	int	count;

	count = 0;
	while (*prog)
	{
		if (*prog == '<' || *prog == '>')
			count++;
		prog++;
	}
	return (count);
}

static char **redirec_list(char *prog, char type)
{
	char	**redirections;
	int		iter;

	redirections = ft_split(prog, type);
	if (!redirections)
		return (NULL);
	if (type == '<')
	{
		iter = 0;
		while (redirections[iter] != NULL)
			iter++;
		free(redirections[iter - 1]);
		redirections[iter - 1] = NULL;
	}
	else if (type == '>')
	{
		free(*redirections);
		redirections = &redirections[1];
	}
	return (redirections);
}

int	chk_and_redirec(char *prog, t_cmd *cmd)
{
	int		redirec_c;

	redirec_c = n_redirecs(prog);
	if (redirec_c == 0)
	{
		cmd->args = ft_split(prog, ' ');
		return (TRUE);
	}
	cmd->redirec = alloc_vector(redirec_c);
	if (!cmd->redirec)
		return (msg_err("chk_and_redirec()", FAILURE));

}
