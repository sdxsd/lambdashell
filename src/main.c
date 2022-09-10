/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/19 21:20:37 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/09/11 01:39:16 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	clean_tokens(t_list **tokenlist)
{
	int			i;
	t_list		*list_head;
	t_token		*token_tmp;
	t_list		*tmp;

	i = 0;
	list_head = (*tokenlist);
	while (list_head)
	{
		token_tmp = list_head->content;
		free(token_tmp->txt);
		tmp = list_head;
		list_head = list_head->next;
		free (tmp);
		i++;
	}
	free (list_head);
	return (0);
}

int	clean_env(t_env **env)
{
	t_env *tmp1;
	t_env *tmp2;

	tmp1 = (*env);
	while (tmp1)
	{
		free (tmp1->key);
		free (tmp1->val);
		tmp2 = tmp1->next;
		free (tmp1);
		tmp1 = tmp2;
	}
	free (tmp1);
	free (env);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_ms *ms;

	ms = ft_calloc(1 + 1, sizeof(t_ms));
	if (init_start())
		return (1);
	if (init_ms(ms))
		return (msg_err("Failed to initialize ms.", 1));
	if (init_env(ms, envp))
		return (msg_err("Failed to initialize env.", 1));
	prompt(ms);

	free (ms->line);
	clean_tokens(&ms->tokens);
	//clean_list(&ms->tokens);
	clean_env(ms->env);
	free (ms);	
	(void)argc;
	(void)argv;
	return 0;
}

/*
builtins made:
- pwd(), saved as ms_pwd()

todo [short-term]
- find out how work with global variables without getting multiple def. error.
- get_env_key_idx(t_env **env, char *key) results in segfault if the key does not exist. Fix this. What is the desired behavior?
*/
