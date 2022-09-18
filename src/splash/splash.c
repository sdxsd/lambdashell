/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   splash.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/14 12:50:16 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/09/18 11:44:25 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	splash()
{
	color_orange();
	printf("%s", SPLASH);
	color_reset();
}

void	clear_screen(void)
{
	write(STDOUT_FILENO, "\x1b[2J", 4);
	write(STDOUT_FILENO, "\x1b[H", 3);
}
