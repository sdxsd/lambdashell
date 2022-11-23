#include "../../include/minishell.h"
#include <stdlib.h>

// NOTE: Thine fruit need not be begotten so.

void dealloc_redir(void *to_free)
{
	t_redirec *redir;

	redir = to_free;
	if (redir)
	{
		if (redir->filename)
			free(redir->filename);
		free(redir);
	}
}

static int	n_redirec(char *prog)
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

static int redirec_list(char *prog, char type, char ***redirs)
{
	int		iter;

	if (!strchr(prog, type))
		return (TRUE);
	*redirs = ft_split(prog, type);
	if (!*redirs)
		return (msg_err("redirec_list()", FAILURE));
	if (type == '<')
	{
		iter = 0;
		while (*redirs[iter] != NULL)
			iter++;
		free(*redirs[iter - 1]);
		*redirs[iter - 1] = NULL;
	}
	else if (type == '>')
	{
		free(**redirs);
		*redirs = &*redirs[1];
	}
	return (TRUE);
}

int	chk_and_redirec(char *prog, t_cmd *cmd)
{
	int		redirec_c;
	char	**args;
	char	*tmp;
	char	**o_redirec;
	char	**i_redirec;

	redirec_c = n_redirec(prog);
	o_redirec = NULL;
	i_redirec = NULL;
	if (redirec_c == 0)
	{
		cmd->args = ft_split(prog, ' ');
		return (TRUE);
	}
	cmd->redirec = alloc_vector(redirec_c);
	if (!cmd->redirec)
		return (msg_err("chk_and_redirec()", FAILURE));
	if (redirec_list(prog, '<', &o_redirec) == FAILURE || \
		redirec_list(prog, '>', &i_redirec) == FAILURE)
	{
		if (i_redirec)
			free_ptr_array(i_redirec);
		if (o_redirec)
			free_ptr_array(o_redirec);
		free_vector(cmd->redirec, dealloc_redir);
		return (msg_err("chk_and_redirec()", FALSE));
	}
	if (i_redirec)
	{
		prog = ft_strrchr(prog, '<');
		while (*prog == ' ')
			prog++;
		while (*prog != ' ')
			prog++;
		if (o_redirec)
		{
			tmp = ft_strndup(prog, prog - ft_strchr(prog, '>'));
			cmd->args = ft_split(tmp, ' ');
		}
		else
			cmd->args = ft_split(prog, ' ');
		return (TRUE);
	}
	return (SUCCESS);
}
