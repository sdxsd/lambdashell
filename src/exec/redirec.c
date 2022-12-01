#include "../../include/minishell.h"
#include <stdlib.h>

// NOTE: Thine fruit need not be begotten so.

/* void dealloc_redir(void *to_free) */
/* { */
/* 	t_redirec *redir; */

/* 	redir = to_free; */
/* 	if (redir) */
/* 	{ */
/* 		if (redir->filename) */
/* 			free(redir->filename); */
/* 		free(redir); */
/* 	} */
/* } */

/* static int	n_redirec(char *prog) */
/* { */
/* 	int	count; */

/* 	count = 0; */
/* 	while (*prog) */
/* 	{ */
/* 		if (*prog == '<' || *prog == '>') */
/* 			count++; */
/* 		prog++; */
/* 	} */
/* 	return (count); */
/* } */

/* static int redirec_list(char *prog, char type, char ***redirs) */
/* { */
/* 	int		iter; */

/* 	if (!strchr(prog, type)) */
/* 		return (TRUE); */
/* 	redirs[0] = ft_split(prog, type); */
/* 	if (!*redirs) */
/* 		return (msg_err("redirec_list()", FALSE)); */
/* 	if (type == '<') */
/* 	{ */
/* 		iter = 0; */
/* 		while (redirs[0][iter] != NULL) */
/* 			iter++; */
/* 		free(redirs[0][iter - 1]); */
/* 		redirs[0][iter - 1] = NULL; */
/* 	} */
/* 	else if (type == '>') */
/* 	{ */
/* 		free(redirs[0][0]); */
/* 		redirs[0][0] = redirs[0][1]; */
/* 		redirs[0][1] = NULL; */
/* 	} */
/* 	return (TRUE); */
/* } */

/* void	strings_to_redirec(char **i, char **o, t_vector *redirec_vec) */
/* { */
/* 	int	iter; */
/* 	int idx; */

/* 	iter = 0; */
/* 	idx = 0; */
/* 	if (i) */
/* 	{ */
/* 		while (o[iter]) */
/* 		{ */
/* 			vec_assign_element(redirec_vec, idx, o[iter]); */
/* 			iter++; */
/* 			idx++; */
/* 		} */
/* 	} */
/* 	iter = 0; */
/* 	if (o) */
/* 	{ */
/* 		while (o[iter]) */
/* 		{ */
/* 			vec_assign_element(redirec_vec, iter, o[iter]); */
/* 			iter++; */
/* 			idx++; */
/* 		} */
/* 	} */
/* } */

/* int	chk_and_redirec(char *prog, t_cmd *cmd) */
/* { */
/* 	int		redirec_c; */
/* 	char	*tmp; */
/* 	char	**o_redirec; */
/* 	char	**i_redirec; */

/* 	redirec_c = n_redirec(prog); */
/* 	o_redirec = NULL; */
/* 	i_redirec = NULL; */
/* 	if (redirec_c == 0) */
/* 	{ */
/* 		cmd->args = ft_split(prog, ' '); */
/* 		return (TRUE); */
/* 	} */
/* 	cmd->redirec = alloc_vector(redirec_c); */
/* 	if (!cmd->redirec) */
/* 		return (msg_err("chk_and_redirec()", FALSE)); */
/* 	if (!redirec_list(prog, '>', &o_redirec) || \ */
/* 		!redirec_list(prog, '<', &i_redirec)) */
/* 	{ */
/* 		if (i_redirec) */
/* 			free_ptr_array(i_redirec); */
/* 		if (o_redirec) */
/* 			free_ptr_array(o_redirec); */
/* 		free_vector(cmd->redirec, dealloc_redir); */
/* 		return (msg_err("chk_and_redirec()", FALSE)); */
/* 	} */
/* 	strings_to_redirec(i_redirec, o_redirec, cmd->redirec); */
/* 	if (i_redirec) */
/* 	{ */
/* 		prog = ft_strrchr(prog, '<'); */
/* 		while (*prog == ' ') */
/* 			prog++; */
/* 		while (*prog != ' ') */
/* 			prog++; */
/* 		if (o_redirec) */
/* 		{ */
/* 			tmp = ft_strndup(prog, prog - ft_strchr(prog, '>')); */
/* 			if (!tmp) */
/* 				return (msg_err("chk_and_redirec()", FALSE)); */
/* 			cmd->args = ft_split(tmp, ' '); */
/* 		} */
/* 		else */
/* 			cmd->args = ft_split(prog, ' '); */
/* 		return (TRUE); */
/* 	} */
/* 	if (o_redirec) */
/* 	{ */
/* 		if (!i_redirec) */
/* 		{ */
/* 			tmp = ft_strndup(prog, prog - ft_strchr(prog, '>')); */
/* 			if (!tmp) */
/* 				return (msg_err("chk_and_redirec()", FALSE)); */
/* 			cmd->args = ft_split(tmp, ' '); */
/* 			free(tmp); */
/* 			dbg_print_lines(o_redirec); */
/* 			dbg_print_lines(cmd->args); */
/* 		} */
/* 		return (TRUE); */
/* 	} */
/* 	return (FALSE); */
/* } */
