/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   colors.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/14 12:54:30 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/09/14 13:33:51 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	color_red()
{
	printf("\033[0;31m");
}

void	color_orange()
{
	printf("\033[38;5;214m");
}

void	color_green()
{
	printf("\033[0;32m");
}

void	color_reset()
{
	printf("\033[0m");
}
