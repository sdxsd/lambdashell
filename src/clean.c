/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clean.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/31 15:07:36 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/08/31 15:07:44 by mikuiper      ########   odam.nl         */
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
