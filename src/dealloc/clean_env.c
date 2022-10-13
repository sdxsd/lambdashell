/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clean_env.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/18 13:25:48 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/09/18 19:03:43 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
