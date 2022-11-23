#include "../../include/minishell.h"
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

static int redirec_list(char *prog, char type, char **redirs)
{
	int		iter;

	if (!strchr(prog, type))
		return (TRUE);
	redirs = ft_split(prog, type);
	if (!redirs)
		return (msg_err("redirec_list()", FAILURE));
	if (type == '<')
	{
		iter = 0;
		while (redirs[iter] != NULL)
			iter++;
		free(redirs[iter - 1]);
		redirs[iter - 1] = NULL;
	}
	else if (type == '>')
	{
		free(*redirs);
		redirs = &redirs[1];
	}
	return (TRUE);
}

int	chk_and_redirec(char *prog, t_cmd *cmd)
{
	int		redirec_c;
	char	**o_redirecs;
	char	**i_redirecs;

	redirec_c = n_redirecs(prog);
	o_redirecs = NULL;
	i_redirecs = NULL;
	if (redirec_c == 0)
	{
		cmd->args = ft_split(prog, ' ');
		return (TRUE);
	}
	cmd->redirec = alloc_vector(redirec_c);
	if (!cmd->redirec)
		return (msg_err("chk_and_redirec()", FAILURE));
	if (redirec_list(prog, '<', o_redirecs) == FAILURE || \
		redirec_list(prog, '>', i_redirecs) == FAILURE)
	{
		if (i_redirecs)
			free_ptr_array(i_redirecs);
		if (o_redirecs)
			free_ptr_array(o_redirecs);
		return (msg_err("chk_and_redirec()", FALSE));
	}

	return (SUCCESS);
}
