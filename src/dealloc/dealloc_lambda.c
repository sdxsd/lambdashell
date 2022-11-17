/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dealloc_lambda.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/16 16:06:44 by sbos          #+#    #+#                 */
/*   Updated: 2022/11/16 16:06:44 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	dealloc_lambda(t_shell *lambda)
{
	if (!lambda)
		return ;
	free_vector(lambda->env, dealloc_env_element);
	ft_free(&lambda->line);
}
