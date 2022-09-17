/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_env.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/17 21:00:17 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/09/17 21:35:50 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	builtin_env(t_ms *ms, int fd)
{
	t_env	*env;

	env = *ms->env;
	while (env)
	{
		if (env->key)
		{
			ft_putstr_fd(env->key, fd);
			ft_putstr_fd("=", fd);
			ft_putstr_fd(env->val, fd);
			ft_putchar_fd('\n', fd);
		}
		env = env->next;
	}
}