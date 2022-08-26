/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clean.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/25 13:57:16 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/08/26 15:38:36 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	clean_dp(char **dp)
{
	int	i;

	i = 0;
	while (dp[i])
	{
		free (dp[i]);
		i++;
	}
	free (dp);
	return (0);
}

// int	clean_ms_wrapper(t_ms *ms)
// {
// 	if (!ms)
// 		return (1);
// 	//clean_ms_env(ms);
// 	return (0);
// }
